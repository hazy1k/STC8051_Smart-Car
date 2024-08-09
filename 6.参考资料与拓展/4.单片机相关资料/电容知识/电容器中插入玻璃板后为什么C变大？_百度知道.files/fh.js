function cf_h(flashsrc,flashwidth,flashheight,flashlink,br){
	if (flashwidth != "100%")
	{
		var tbWidth = parseInt(flashwidth)+28;
	}
	else
	{
		var tbWidth =flashwidth;
	}
	document.write("<table width="+tbWidth+" height="+flashheight+" border=0 cellpadding=0 cellspacing=0>");
	document.write("<tr><td style=\"border:3px solid #BFBFBF;\">");
	document.write("<div style=\"position:relative\">");
	document.write("<embed style=\"position:absolute;z-index:0\" src="+flashsrc+" quality=\"high\" width="+flashwidth+" height="+flashheight+" TYPE=\"application/x-shockwave-flash\" PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash\" wmode=\"opaque\"></embed>");
	document.write("<div style=\"position:relative;filter:alpha(opacity=0);-moz-opacity:0;z-index:10;left:0;top:0;background:transparent !important;background:#cdeaf6;width:"+flashwidth+";height:"+flashheight+"px;\">");
	document.write("<a href="+flashlink+" target=\"_blank\" style=\"cursor:pointer;display:block;width:"+flashwidth+";height:"+flashheight+"px;\"></a>");
	document.write("</div>");
	document.write("</div>");
	document.write("</td><td style=\"background:url(http://eiv.baidu.com/mapm2/rt.gif) no-repeat left top;width:28px;\"></td></tr></table>");
	if (br=="1") {
	document.write("<br>");
	}
}

function cf1_h(flashsrc,flashwidth,flashheight,br){
	if (flashwidth != "100%")
	{
		var tbWidth = parseInt(flashwidth)+28;
	}
	else
	{
		var tbWidth =flashwidth;
	}
	document.write("<table width="+tbWidth+" height="+flashheight+" border=0 cellpadding=0 cellspacing=0>");
	document.write("<tr><td style=\"border:3px solid #BFBFBF;\">");
	document.write("<embed src=\""+flashsrc+"\" quality=high pluginspage=\"http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash\" type=\"application/x-shockwave-flash\" width="+flashwidth+" height="+flashheight+" align=center wmode=\"opaque\"></embed>");
	document.write("</td><td style=\"background:url(http://eiv.baidu.com/mapm2/rt.gif) no-repeat left top;width:28px;\"></td></tr></table>");
	if (br=="1") {
	document.write("<br>");
	}
}