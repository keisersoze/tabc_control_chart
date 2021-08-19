# Export the "BankAccount" C++ class by explicitly requesting BankAccount be
# exported via roxygen2's export tag.
#' @exportPattern "^[[:alpha:]]+"

loadModule(module = "test_module", TRUE)
