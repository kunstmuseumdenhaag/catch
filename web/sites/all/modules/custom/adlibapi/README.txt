ADLIBAPI
========
Set of modules which provide drupal integration with the AdlibSoft adlib museum software.

Features
========
- Set of api functions to do adlib calls to an adlib database
- Exportable adlib database settings
- Feeds integration to import and update an adlib database to Drupal
- Image module to 'lazy load' images from adlib into a cck-imagefield

Requirements
============
- CTools 1.x
  http://drupal.org/project/ctools
- Date 2.x
  http://drupal.org/project/date
- Feeds 1.x
  http://drupal.org/project/feeds
  
Installation
============
To import an adlib database to Drupal, take the following steps:
- Enable adlibapi and adlibapi_feeds
- Create a new adlib database setting at 'admin/build/adlibapi', or use the supplied adlib_sandbox setting
- Create a new Feed importer at 'admin/build/feeds'
- Change the fetcher to 'Adlib Fetcher'
- Go to the settings of the 'Adlib Fetcher'
- Select an adlib database
- In order to use the adlib parser select the unstructered xml type.
- Select the fields to retrieve from the adlib database
- Change the parser to the adlib parser (alternatively the xpath parser can be used)
- Now first create the mappings at the processor (select an adlib expression)
- At the parser settings, map one or more adlib fields to the drupal fields using the tokens.
- The progress of an import/update can be tracked at the fetcher settings.

