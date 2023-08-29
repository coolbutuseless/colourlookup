
<!-- README.md is generated from README.Rmd. Please edit that file -->

# colourlookup

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
<!-- badges: end -->

`{colourlookup}` is a proof-of-concept technical demonstration of an
order-preserving minimal perfect hash in application to R colour
handling.

Using a hash to match colour names can be of the order of ~100x faster
than a linear search.

### What’s in the box

- `col_to_rgb()` a version of `col2rgb()` which uses hash lookup rather
  than linear search to match R colour names to RGBA values. \####
  Benchmark

This is the results of a benchmark comparing R’s `col2rgb()` (using
linear name search) with this package’s `col_to_rgb()` using a hashed
name lookup.

See end of this page for benchmark code.

| expression    |    min | median |     itr/sec | mem_alloc |
|:--------------|-------:|-------:|------------:|----------:|
| hash lookup   | 6.85µs | 7.95µs | 122044.0319 |    19.7KB |
| linear lookup | 1.04ms | 1.07ms |    928.2638 |    20.7KB |

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" />

# Order-preserving minimal perfect hash

### Hash

A **hash** of a string is just a combination of the bits in the string
to produce another value.

Useful hashes are those that produce markedly different output for
slightly different inputs. e.g. CRC32, SHA1, MD5

The `hash()` function in `{rlang}` is a good example of such a hash.
Note how different the output of the hash is when only one character has
changed.

``` r
rlang::hash("hello")
#> [1] "48b69f4c216ac6e6dd32d65a6c53451e"
rlang::hash("hello!")
#> [1] "e3e018855766ef8629be247a8f3cc443"
```

### Hash collisions

Due to the limits of reality, hashing arbitrary length strings into
shorter strings will mean that for some special cases different strings
will produce the same hashed output (see [the pigeonhole
principle](https://en.wikipedia.org/wiki/Pigeonhole_principle)). This is
known as a [hash
collision](https://en.wikipedia.org/wiki/Hash_collision)

Hash collisions mean that you don’t know for sure which string produced
a particular hash, and so extra context information is kept to help
disambiguate when this occurs.

    hash("apple")  => 1034  # Collision with "carrot"
    hash("banana") => 245
    hash("carrot") => 1034  # Collision with "apple"

### Perfect Hashing

[Perfect hashing](https://en.wikipedia.org/wiki/Perfect_hash_function)
is when the input data is known and fixed, and there exists a hash that
has no collisions.

    hash("apple")  => 1034 
    hash("banana") => 245
    hash("carrot") => 876  

### Minimal Perfect Hashing

[Minimal Perfect
Hashing](https://en.wikipedia.org/wiki/Perfect_hash_function#Minimal_perfect_hash_function)
is when a perfect hash can map *n* strings onto *n* consecutive
integers.

Note: the order of the integers does not have to match the original
order of the strings.

    hash("apple")  => 3 
    hash("banana") => 1
    hash("carrot") => 2  

### Order-Preserving Minimal Perfect Hashing

[Order-Preserving minimal perfect
hashing](https://en.wikipedia.org/wiki/Perfect_hash_function#Order_preservation)
is when the *n* strings match to *n* consecutive integers in the same
order as the strings were defined.

As an example, if we have 3 strings “apple”, “banana” and “carrot”, an
*order-preserving minimal perfect hash* would have the following result:

    hash("apple")  => 1
    hash("banana") => 2
    hash("carrot") => 3

## R colours

R has 657 built-in colour names it understands e.g. “red”, “hotpink”.
This is a fixed list of colours that has not changed membership since
originally introduced (as far as I know).

When looking up colours with `col2rgb()`, R does a linear search over
these 657 colours to find the values to return.

Since the list of colours is fixed and known, this colour lookup could
be replaced by a hash lookup.

For this package I have used an *order-preserving minimal perfect hash*
to do this lookup.

## Creating the C code for the minimal perfect hash

There are a number of programs which will produce C code to do minimal
perfect hashing of a list of strings e.g. `gperf`, `cmph`.

I chose `mph` as described in [A Family of Perfect Hashing
Methods(pdf)](https://staff.itee.uq.edu.au/havas/TR0242.pdf)

- Download and compile
  \[<http://www.ibiblio.org/pub/Linux/devel/lang/c/mph-1.2.tar.gz>\]
- In R: `writeLines(colors(), "input.txt")`
- On the command line: `mph < input.txt | emitc > hash.c`
- Incorporate the `hash.c` code into this package and add the
  `col_to_rgb()` wrapper which uses it.

## Installation

You can install from
[GitHub](https://github.com/coolbutuseless/colourlookup) with:

``` r
# install.package('remotes')
remotes::install_github('coolbutuseless/colourlookup')
```

## Example

``` r
library(colourlookup)

col_to_rgb(c("hotpink", "#abc", "#aabb99", "#aabb9980"))
#>       [,1] [,2] [,3] [,4]
#> red    255  170  170  170
#> green  105  187  187  187
#> blue   180  204  153  153
#> alpha  255    0    0  128
```

# Benchmarks

## Looking up RGBA values for all named colours in R

``` r
cols <- colours()

res <- bench::mark(
  col_to_rgb(cols),
  col2rgb(cols, alpha = TRUE),
  check = TRUE
)
```

| expression    |    min | median |     itr/sec | mem_alloc |
|:--------------|-------:|-------:|------------:|----------:|
| hash lookup   | 6.85µs | 7.95µs | 122044.0319 |    19.7KB |
| linear lookup | 1.04ms | 1.07ms |    928.2638 |    20.7KB |

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" />

## Acknowledgements

- R Core for developing and maintaining the language.
- CRAN maintainers, for patiently shepherding packages onto CRAN and
  maintaining the repository
