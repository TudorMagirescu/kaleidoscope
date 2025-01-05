# Kaleidoscope

My own implementation of a LLVM compiler for the *Kaleidoscope* language. The ideas used closely follow the official [Kaleidoscope tutorial](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html).

## Grammar

$program$ $\rightarrow$ $stmt$ **;** $program$\
$program$ $\rightarrow$ $\epsilon$

$stmt$ $\rightarrow$ $expr$\
$stmt$ $\rightarrow$ $funcDef$\
$stmt$ $\rightarrow$ $externDef$

$funcDef$ $\rightarrow$ **def** $funcSign$ { $expr$ }\
$externDef$ $\rightarrow$ **extern** $funcSign$\
$funcSign$ $\rightarrow$ $id$**(**$idList$**)**

$expr$ $\rightarrow$ $num$\
$expr$ $\rightarrow$ $idExpr$\
$idExpr$ $\rightarrow$ $callExpr$ | $id$\
$callExpr$ $\rightarrow$ $id$**(**$exprList$**)**\
$exprList$ $\rightarrow$ $expr$**,**$exprList$ | $\epsilon$

$num$ $\rightarrow$ $[0-9]^*.[0-9]^*$\
$id$ $\rightarrow$ $[a-zA-Z][a-zA-Z0-9]^*$\
$idList$ $\rightarrow$ $id$**,**$idList$ | $\epsilon$