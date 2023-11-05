*{
	background-color : #444444;
	color : #dddddd;
}
QGroupBox {
    border: 1px solid ;
	border-color: rgb(156, 156, 156);
    margin-top: 27px;
    font-size: 14px;
    border-radius: 3px;
}

QGroupBox::title {
	top:15px;
	left : 15px;
    subcontrol-origin: margin;
    subcontrol-position: top left;
    padding: 0px 2px;
    color: rgb(255, 255, 255);
}

QPushButton {
	background-color: rgb(176, 80, 255);
	border-style: outset;
	border-width: 1px;
	border-radius: 2px;
	border-color: rgb(17, 17, 17);
}
  QPushButton:pressed {
      background-color: rgb(224, 0, 0);
      border-style: inset;
  }

QSpinBox {
	padding-right: 15px; /* make room for the arrows */
	border: 1px solid;
	border-radius : 2px;
	border-color: rgb(154, 154, 154);
	border-width: 1;
}

QSpinBox::up-button {
	subcontrol-origin: border;
	subcontrol-position: top right; /* position at the top right corner */
	border-top-left-radius:2px;
	background-color: rgb(168, 168, 168);
	width: 10px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */
	border-width: 1px;
}

  QSpinBox::up-button:hover {
      border-image: url(:/images/spinup_hover.png) 1;
  }

  QSpinBox::up-button:pressed {
      border-image: url(:/images/spinup_pressed.png) 1;
  }

  QSpinBox::up-arrow {
      image: url(:/images/up_arrow.png);
      width: 7px;
      height: 7px;
  }

  QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off { /* off state when value is max */
     image: url(:/images/up_arrow_disabled.png);
  }

QSpinBox::down-button {
	subcontrol-origin: border;
	subcontrol-position: bottom right; /* position at the top right corner */
	border-bottom-left-radius:2px;
	background-color: rgb(168, 168, 168);
	width: 10px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */
	border-width: 1px;
}

  QSpinBox::down-button:hover {
      border-image: url(:/images/spindown_hover.png) 1;
  }

  QSpinBox::down-button:pressed {
      border-image: url(:/images/spindown_pressed.png) 1;
  }

  QSpinBox::down-arrow {
      image: url(:/images/down_arrow.png);
      width: 7px;
      height: 7px;
  }

  QSpinBox::down-arrow:disabled,
  QSpinBox::down-arrow:off { /* off state when value in min */
     image: url(:/images/down_arrow_disabled.png);
  }

