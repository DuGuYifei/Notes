# dataframe用某列做index

```R
rownames(dataset) <- dataset$voivodeship
dataset$voivodeship <- NULL
```