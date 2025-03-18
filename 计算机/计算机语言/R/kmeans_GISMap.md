# kmeans_GISMap
```r
---
title: "Final project - Analyzing population"
author: "Yifei Liu s188026"
date: "24/1/2023"
output:
  rmdformats::readthedown:
    highlight: kate
    toc_float: true
    toc_depth: 4
---
```

```{r setup, include=FALSE}
knitr::opts_chunk$set(echo = TRUE)
```

**RPubs Link**: [https://rpubs.com/YifeiLiu/AnalyzingPopulation](https://rpubs.com/YifeiLiu/AnalyzingPopulation)

# 1. Packages needed
```{r message=FALSE, warning=FALSE, paged.print=FALSE}
# install.packages("leaflet")
# install.packages("stats")
# install.packages("factoextra")
library(leaflet)
library(raster)
library(factoextra)
```

# 2. Get the polygons data
```{r message=FALSE, warning=FALSE}
polygons <- getData('GADM', country='Poland', level=1)
```


# 3. Prepare statistic datasets

1. Population: [Wiki Link (click to go)](https://en.wikipedia.org/wiki/Voivodeships_of_Poland)
2. city number : [pl gov statistic centre (click to go)](https://eteryt.stat.gov.pl/eteryt/raporty/WebRaportZestawienie.aspx)

```{r}
# dataset$NAME_1

voivodeship<-c(
  "Dolnośląskie", "Kujawsko-Pomorskie", "Łódzkie"       , "Lubelskie"          , "Lubuskie"     ,      
  "Małopolskie" , "Mazowieckie"       , "Opolskie"      , "Podkarpackie"       , "Podlaskie"    ,      
  "Pomorskie"   , "Śląskie"           , "Świętokrzyskie", "Warmińsko-Mazurskie", "Wielkopolskie",
  "Zachodniopomorskie"
)

population <- c(2903000,2056000,18219,2104000,995000,3399000,5432000,966000,2098000,1182000,2355000,4501000,1216000,1423000,3486000,1694000)
city_num <- c(26,19,21,20,12,19,37,11,21,14,16,17,13,19,31,18)

dataset<-data.frame(voivodeship, population)
rownames(dataset) <- dataset$voivodeship
dataset$voivodeship <- NULL

polygons$population <- population
polygons$city_num <- city_num
``` 

# 4. k-means
1. Estimate the optimal number of clusters
2. compute kmeans
3. Visualize clusters to help determine
4. Access to result

## 4.1 Estimate the optimal number of clusters
```{r}
dataset.scaled <- scale(dataset)
fviz_nbclust(dataset.scaled, kmeans, method = "wss") +
geom_vline(xintercept = 2, linetype = 2)

fviz_nbclust(dataset.scaled, kmeans, method = "silhouette") +
geom_vline(xintercept = 2, linetype = 2)
```

In "wss" plot, it represents the variance within the clusters. It decreases as k increases, but it can be seen a “elbow” at k = 2 or 4 or 5. This bend indicates that additional clusters beyond the fourth have little value.

In "silhouette" plot, we can see dataset has a obvious peak in k = 2 and k = 5.

So we can try both 2, 4 and 5 and decide at last.

## 4.2 compute kmeans
```{r}
set.seed(123)
km.res2 <- kmeans(dataset, 2, nstart = 25)
km.res2
km.res4 <- kmeans(dataset, 4, nstart = 25)
km.res4
km.res5 <- kmeans(dataset, 5, nstart = 25)
km.res5
```

Cluster means: a matrix, which rows are cluster number (1 to 4) and columns are variables
Clustering vector: A vector of integers (from 1:k) indicating the cluster to which each point is allocated

So the detailed display see 4.3 and 4.4.

## 4.3 Visualize clusters to help determine
To help to see the result more easily, we add one more useless column.

The city_num is very small when compare to population, so it will not influence the result. The result show below also prove this.

When look plot, we only need focus the population dimension, e.g. the distance in x-axis.

```{r}
vis_dataset<- cbind(dataset, city_num)
```

### 4.3.1 k = 2
```{r warning=FALSE}
km.res2.vis <- kmeans(vis_dataset, 2, nstart = 25)
km.res2.vis
fviz_cluster(km.res2.vis, vis_dataset,
             palette = c("#2E9FDF", "#00AFBB"), 
             geom = "point",
             ellipse.type = "convex", 
             ggtheme = theme_bw())
```

1. The gap between this two cluster is not too far when compare to the gap in the gap, so we can say it is not the best k value.

2. The means prove that city_num doesn't influence the result, so we can visualization by this way.

### 4.3.2 k = 4
```{r echo=FALSE}
km.res4.vis <- kmeans(vis_dataset, 4, nstart = 25)
km.res4.vis
fviz_cluster(km.res4.vis, vis_dataset,
             palette = c("#2E9FDF", "#00AFBB", "#E7B800", "#E7B850"), 
             geom = "point",
             ellipse.type = "convex", 
             ggtheme = theme_bw())
```

1. The gap for the most left point is significantly big, we can assume when k = 5, it will divide this point out as single cluster. And next step prove this assumption is true.

2. The means prove that city_num doesn't influence the result, so we can visualization by this way.

### 4.3.3 k = 5
```{r echo=FALSE}
km.res5.vis <- kmeans(vis_dataset, 5, nstart = 25)
km.res5.vis
fviz_cluster(km.res5.vis, vis_dataset,
             palette = c("#2E9FDF", "#00AFBB", "#E7B800", "#E7B850", "#00AFCB"), 
             geom = "point",
             ellipse.type = "convex", 
             ggtheme = theme_bw())
```

1. It prove the assumption in 4.3.2 is correct, and we can choose k = 5 as optimization.

2. The means prove that city_num doesn't influence the result, so we can visualization by this way.

## 4.4 Access to result
* Display results
```{r}
cbind(dataset, cluster = km.res5$cluster)
```

* Cluster size
```{r}
km.res5$size
```

* Cluster means
```{r}
km.res5$centers
```


# 5. Map (leaflet)
1. add polygon
2. give popup for each polygon with
  * name of voivodeship
  * population
  * number of cities in the voivodeship
3. additional
  * make color depends on **population**
  * **highlight** the voivodeship when it is chosen
  
## 5.1 Center of view
```{r}
pl_coordinates <- c(51.93046841624075, 18.913610940888134)
```


## 5.2 popup
```{r}
pop = paste0(
  "<b>Voivodoship: </b>", polygons$NAME_1, "<br>",
  "<b>population: </b>", polygons$population, "<br>",
  "<b>city quantity: </b>", polygons$city_num, "<br>"
)
```

## 5.3 Color based on population
```{r}
color_slope = 21302

color_popu = rgb(polygons$population / color_slope / 255, polygons$population / color_slope / 255, 0)
```

## 5.4 highlight
```{r}
highlight = highlightOptions(color='white',weight=2,bringToFront = TRUE)
```


## 5.5 Create map
```{r}
leaflet() %>%
  setView(lng = pl_coordinates[2], lat = pl_coordinates[1], zoom = 6) %>%
  addProviderTiles("OpenStreetMap.Mapnik") %>%
  addPolygons(
    data = polygons, 
    weight = 2, 
    opacity = 0.9, 
    fillColor = color_popu, 
    highlightOptions = highlight,
    popup = pop
  )
```

