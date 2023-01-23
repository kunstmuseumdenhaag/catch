<?php
class AdlibImageQuery {
  /*
   * Image settings.
   */
  protected $width = 600;
  protected $height = 600;
  protected $filename;
  /*
   * Scale mode has two possible settings:
   * 1) fit
   * 2) fill
   */
  protected $scalemode;
  /*
   * Fillmode has three possible settings
   * 1) topleft
   * 2) center
   * 3) bottomright
   */
  protected $fillmode;
  /*
   * Canvas color and corner colors are strings: excerpt from adlibapi documentation:
   * determines the colour of the empty part of the canvas of the box
   * specified using the width and height parameters.
   * Colour names are determined by the .NET Framework 4 Color Structure object,
   * which is documented on: MSDN.
   * Examples of colour names are: black, white, transparent, orange, etc.
   */
  protected $canvascolor;
  protected $cornercolor;

  protected $cornerradius;
  /*
   * Constants for fillmode and scalemode
   */
  const SCALEMODE_FIT = 'fit';
  const SCALEMODE_FILL = 'fill';
  const FILLMODE_TOPLEFT = 'topleft';
  const FILLMODE_CENTER = 'center';
  const FILLMODE_BOTTOMRIGHT = 'bottomright';

  /**
   * Constructor
   */
  function __construct($filename) {
    $this->filename = $filename;
  }

  /**
   * Desired width
   * @param integer $width
   */
  public function setWidth($width) {
    $this->width = $width;
  }

  /**
   * Desired height
   * @param integer $height
   */
  public function setHeight($height) {
    $this->height = $height;
  }

  /**
   * Set the filename of the image
   * @param string $filename
   */
  public function setFilename($filename) {
    $this->filename = $filename;
  }

  /**
   * Set the scalemode.
   * Use the class constants to set the scalemode. Other strings will not work!
   * @param string $scalemode
   *   use class constants to set.
   */
  public function setScaleMode($scalemode) {
    if ($scalemode == $this->SCALEMODE_FIT || $scalemode == $this->SCALEMODE_FILL) {
      $this->scalemode = $scalemode;
    }
  }

  /**
   * Set the fillmode.
   * Use the class constants to set the fillmode. Other strings will not work!
   * @param string $fillmode
   *   use class constants to set.
   */
  public function setFillMode($fillmode) {
    if ($fillmode == $this->FILLMODE_TOPLEFT || $fillmode == $this->FILLMODE_CENTER || $fillmode == $this->FILLMODE_FIT) {
      $this->scalemode = $scalemode;
    }
  }

  /**
   * Set canvas color.
   * @param string $color
   *  Colour names are determined by the .NET Framework 4 Color Structure object,
   *  which is documented on: MSDN.
   *  Examples of colour names are: black, white, transparent, orange, etc.
   */
  public function setCanvasColor($color) {
    $this->canvascolor = $color;
  }

  /**
   * Set corner color.
   * @param string $color
   *  Colour names are determined by the .NET Framework 4 Color Structure object,
   *  which is documented on: MSDN.
   *  Examples of colour names are: black, white, transparent, orange, etc.
   */
  public function setCornerColor($color) {
    $this->cornercolor = $color;
  }

  /**
   * Set the corner radius of the picture
   * @param integer $radius
   * 	radius should be gt 10
   */
  public function setCornerRadius($radius) {
    if ($radius >= 10) {
      $this->cornerradius = $radius;
    }
  }

  /**
   * Return the querystring to retrieve the image
   * @return
   * 	querystring
   * TODO: Check if url-encode is needed.
   */
  public function getQueryString() {
    $queryparts = array();
    $queryparts[] = 'value=' . $this->filename;
    if (isset($this->width)) {
      $queryparts[] = 'width=' . $this->width;
    }
    if (isset($this->height)) {
      $queryparts[] = 'height=' . $this->height;
    }
    if (isset($this->scalemode)) {
      $queryparts[] = 'scalemode=' . $this->scalemode;
    }
    if (isset($this->canvascolor)) {
      $queryparts[] = 'canvascolor=' . $this->canvascolor;
    }
    if (isset($this->cornercolor)) {
      $queryparts[] = 'cornercolor=' . $this->cornercolor;
    }
    if (isset($this->cornerradius)) {
      $queryparts[] = 'cornerradius=' . $this->cornerradius;
    }
    $querystring = implode('&', $queryparts);
    return $querystring;
  }

}