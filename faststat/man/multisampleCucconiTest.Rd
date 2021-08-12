\name{multisampleCucconiTest}
\alias{multisampleCucconiTest}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
permutation multisample Cucconi test
}
\description{
Performs a permutation multisample Cucconi test. Returns the estimated p-value as well as the multisample Cucconi statistics obtained from the observed data.
}
\usage{
multisampleCucconiTest(samples, B)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{samples}{
a list of samples.
}
  \item{B}{
the number of permutations considered to estimate the p-value of the test.
}
}
\details{
%%  ~~ If necessary, more details than the description above ~~
}
\value{
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
A numeric vector whose first value is the multisample Cucconi statistics obtained from the observed data, and whose second value is the estimated p-value of the test.
}
\references{
%% ~put references to the literature/web site here ~
}
\author{
Filippo Maganza
}
\note{
%%  ~~further notes~~
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
%% ~~objects to See Also as \code{\link{help}}, ~~~
}
\examples{
# beef
x1=c(495,477,425,322,482,587,370,322,479,375,330,300,386,401,645,440,317,
319,298,253)

# poultry
x2=c(458,506,473,545,496,360,387,386,507,393,405,372,144,511,405,428,339)

# meat
x3=c(430,375,396,383,387,542,359,357,528,513,426,513,358,581,588,522,545)

B = 10000

mc.stat = multisampleCucconiTest(list(x1,x2,x3), B)

print (mc.stat)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory (show via RShowDoc("KEYWORDS")):
% \keyword{ ~kwd1 }
% \keyword{ ~kwd2 }
% Use only one keyword per line.
% For non-standard keywords, use \concept instead of \keyword:
% \concept{ ~cpt1 }
% \concept{ ~cpt2 }
% Use only one concept per line.
