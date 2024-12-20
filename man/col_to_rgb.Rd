% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/col_to_rgb.R
\name{col_to_rgb}
\alias{col_to_rgb}
\title{Fast conversion of colors-as-strings to a matrix of RGBA integers}
\usage{
col_to_rgb(col)
}
\arguments{
\item{col}{Character vector of color names. Supports all R color names
(e.g. "red", "hotpink") and hex colors of the form:  "#RRGGBBAA", 
"#RRGGBB", "#RGBA" and "#RGB".}
}
\value{
An integer matrix with four rows and number of columns 
  the length of the input.
}
\description{
This is a replacement for \code{grDevices::col2rgb()}, and can be
100 times faster.
}
\examples{
col_to_rgb(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
}
