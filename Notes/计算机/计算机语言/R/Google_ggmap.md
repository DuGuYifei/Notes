# Google_ggmap

## API key
```R
apiKey = '.........'
register_google(apiKey)
```

## Get localtion
```R
locs <- c('Małopolskie', 'Śląskie', 'Wielkopolskie', 'Zachodniopomorskie', 'Lubuskie', 'Dolnośląskie', 'Opolskie', 'Kujawsko-pomorskie', 'Warmińsko-mazurskie', 'Pomorskie', 'Łódzkie', 'Świętokrzyskie', 'Lubelskie', 'Podkarpackie', 'Podlaskie', 'Mazowiecki')
locations<-geocode(locs)
```