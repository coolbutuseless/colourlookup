

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Convert colours-as-strings to a matrix of RGBA integers
#' 
#' This is a proof-of-concept drop-in replacement for \code{grDevices::col2rgb()}
#' which uses an order-preserving minimal perfect hash to lookup R colour
#' names.
#' 
#' @param col Character vector of colour names. Supports all R colour names
#'        (e.g. "red", "hotpink") and hex colours of the form:  "#RRGGBBAA", 
#'        "#RRGGBB", "#RGBA" and "#RGB".  
#'        
#' @examples
#' col_to_rgb(c("hotpink", "#abc", "#aabb99", "#aabb9980"))
#' 
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
col_to_rgb <- function(col) {
  .Call(col_to_rgb_, col)
}

