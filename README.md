
Sanitize for Fisioterapia-Online.com (fisio_sanitize)
======================

## Overview

fisio_sanitize is a custom drush command for sanitize database.


## Requirements
* Drush 6.x

## To install

You have two option to install.
* On project modules.
* On local drush.

### Project modules
```
cd your_project/sites/*/modules
git clone https://github.com/isarea/fisio_sanitize.git
```

### Local drush
```
cd ~/.drush
git clone https://github.com/isarea/fisio_sanitize.git
```

## Use
### Using with drush sql-sanitize
If you use drush sql-sanitize (drush sqlsan) you have additional awnser to sanitize custom tables.
```
drush sqlsan
```
### Using with drush fisio-sanitize
If you use drush fisio-sanitize (drush fisa) you have sanitize custom tables for fisioterapia-online.
```
drush fisa
```
