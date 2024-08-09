/******************************************************************************
  SupeSite/X-Sapce - common js for SS/XS
  Copyright 2001-2006 Comsenz Inc. (http://www.comsenz.com)
*******************************************************************************/
function getbyid(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (document.all) {
		return document.all[id];
	} else if (document.layers) {
		return document.layers[id];
	} else {
		return null;
	}
}

var isIE = navigator.userAgent.toLowerCase().indexOf('ie');

function getTipDiv(e) {
	if(getbyid("xspace-tipDiv")) {
		divElement = getbyid("xspace-tipDiv");
	} else {
		var divElement = document.createElement("DIV");
		divElement.id = "xspace-tipDiv";
		document.body.appendChild(divElement);
	}
	divElement.className = "xspace-ajaxdiv";
	divElement.style.cssText = "width:400px;";
		
	var offX = 4;
	var offY = 4;
	var width = 0;
	var height = 0;
	var scrollX = 0;
	var scrollY = 0;  
	var x = 0;
	var y = 0;
		
	if (window.innerWidth) width = window.innerWidth - 18;
	else if (document.documentElement && document.documentElement.clientWidth) 
		width = document.documentElement.clientWidth;
	else if (document.body && document.body.clientWidth) 
		width = document.body.clientWidth;
		
	
	if (window.innerHeight) height = window.innerHeight - 18;
	else if (document.documentElement && document.documentElement.clientHeight) 
		height = document.documentElement.clientHeight;
	else if (document.body && document.body.clientHeight) 
		height = document.body.clientHeight;
	

	if (typeof window.pageXOffset == "number") scrollX = window.pageXOffset;
	else if (document.documentElement && document.documentElement.scrollLeft)
		scrollX = document.documentElement.scrollLeft;
	else if (document.body && document.body.scrollLeft) 
		scrollX = document.body.scrollLeft; 
	else if (window.scrollX) scrollX = window.scrollX;
				
	  
	if (typeof window.pageYOffset == "number") scrollY = window.pageYOffset;
	else if (document.documentElement && document.documentElement.scrollTop)
		scrollY = document.documentElement.scrollTop;
	else if (document.body && document.body.scrollTop) 
		scrollY = document.body.scrollTop; 
	else if (window.scrollY) scrollY = window.scrollY;
		
	x=e.pageX?e.pageX:e.clientX+scrollX;
	y=e.pageY?e.pageY:e.clientY+scrollY;

	if(x+divElement.offsetWidth+offX>width+scrollX){
		x=x-divElement.offsetWidth-offX;
		if(x<0)x=0;
	}else x=x+offX;
	if(y+divElement.offsetHeight+offY>height+scrollY){
		y=y-divElement.offsetHeight-offY;
		if(y<scrollY)y=height+scrollY-divElement.offsetHeight;
	}else y=y+offY;

	divElement.style.left = x+"px";
	divElement.style.top = y+"px";
	
}

function tagshow(e, tagname) {

	getTipDiv(e);
	var x = new Ajax('statusid', 'XML');
		
	x.get(siteUrl+'/batch.tagshow.php?tagname='+tagname, function(s){
		divElement = getbyid("xspace-tipDiv");
		divElement.innerHTML = s.lastChild.firstChild.nodeValue;
	});
}

function joinfriend(uid) {
	var x = new Ajax('statusid', 'XML');
		
	x.get(siteUrl+'/batch.common.php?action=joinfriend&uid='+uid, function(s){
		alert(s.lastChild.firstChild.nodeValue);
	});
}

function deletetrack(itemid) {
	var x = new Ajax('statusid', 'XML');

	x.get(siteUrl+'/batch.track.php?action=delete&itemid='+itemid, function(s){
		alert(s.lastChild.firstChild.nodeValue);
	});
}

function taghide() {
	var tip = getbyid("xspace-tipDiv");
	tip.style.display = 'none';
}

function addFirstTag() {
	var lists=new Array;
	lists=document.getElementsByTagName('ul');
	for(i=0;i<lists.length;i++){
		lists[i].firstChild.className+=' first-child';
	}
}

function setTab(area,id) {
	var tabArea=document.getElementById(area);

	var contents=tabArea.childNodes;
	for(i=0; i<contents.length; i++) {
		if(contents[i].className=='tabcontent'){contents[i].style.display='none';}
	}
	document.getElementById(id).style.display='';

	var tabs=document.getElementById(area+'tabs').getElementsByTagName('a');
	for(i=0; i<tabs.length; i++) { tabs[i].className='tab'; }
	document.getElementById(id+'tab').className='tab curtab';
	document.getElementById(id+'tab').blur();
}

function ColExpAllIntro(listid,obj) {
	var ctrlText = obj;
	var list = getbyid(listid);
	if(list.className == 'cleanlist') {
		list.className = 'messagelist';
		ctrlText.innerHTML = '只列出标题';
		ctrlText.className = 'more minus';
	}else{
		list.className = 'cleanlist';
		ctrlText.innerHTML = '列出标题和摘要';
		ctrlText.className = 'more';
	}
}

function OpenWindow(url, winName, width, height) {
	xposition=0; yposition=0;
	if ((parseInt(navigator.appVersion) >= 4 )) {
		xposition = (screen.width - width) / 2;
		yposition = (screen.height - height) / 2;
	}
	theproperty= "width=" + width + ","
	+ "height=" + height + ","
	+ "location=0,"
	+ "menubar=0,"
	+ "resizable=1,"
	+ "scrollbars=1,"
	+ "status=0,"
	+ "titlebar=0,"
	+ "toolbar=0,"
	+ "hotkeys=0,"
	+ "screenx=" + xposition + "," //仅适用于Netscape
	+ "screeny=" + yposition + "," //仅适用于Netscape
	+ "left=" + xposition + "," //IE
	+ "top=" + yposition; //IE 
	window.open(url, winName, theproperty);
}

function joinfavorite(itemid) {
	var x = new Ajax('statusid', 'XML');
	x.get(siteUrl + '/batch.common.php?action=joinfavorite&itemid='+itemid, function(s) {
		alert(s.lastChild.firstChild.nodeValue);
	});
}

function report(itemid) {
	var x = new Ajax('statusid', 'XML');
	x.get(siteUrl + '/batch.common.php?action=report&itemid='+itemid, function(s) {
		alert(s.lastChild.firstChild.nodeValue);
	});
}

function showajaxdiv(url, width) {
	var x = new Ajax('statusid', 'XML');
	x.get(url, function(s) {
		if(getbyid("xspace-ajax-div")) {
			var divElement = getbyid("xspace-ajax-div");
		} else {
			var divElement = document.createElement("DIV");
			divElement.id = "xspace-ajax-div";
			divElement.className = "xspace-ajaxdiv";
			document.body.appendChild(divElement);
		}
		divElement.style.cssText = "width:"+width+"px;";
		var userAgent = navigator.userAgent.toLowerCase();
		var is_opera = (userAgent.indexOf('opera') != -1);
		var clientHeight = scrollTop = 0; 
		if(is_opera) {
			clientHeight = document.body.clientHeight /2;
			scrollTop = document.body.scrollTop;
		} else {
			clientHeight = document.documentElement.clientHeight /2;
			scrollTop = document.documentElement.scrollTop;
		}
		divElement.innerHTML = s.lastChild.firstChild.nodeValue;
		divElement.style.left = (document.documentElement.clientWidth /2 +document.documentElement.scrollLeft - width/2)+"px";
		divElement.style.top = (clientHeight +　scrollTop - divElement.clientHeight/2)+"px";
		
	});	
}


function getMsg() {
	if (GetCookie('readMsg')!='1') {
		var msgDiv = document.createElement('div');
		msgDiv.id = 'xspace-sitemsg';
		msgDiv.innerHTML = "<h6><span onclick='closeMsg();' class='xspace-close'>关闭</span>公告:</h6><div>"+siteMsg+"<p class='xspace-more'><a href='"+siteUrl+"/index.php?action/announcement' target='_blank'>MORE</a></p></div>";
		document.body.insertBefore(msgDiv,document.body.firstChild);
		
		showMsg();
	}
}
function floatMsg() {
	window.onscroll = function() {
		document.getElementById('xspace-sitemsg').style.bottom = '10px';
		document.getElementById('xspace-sitemsg').style.background = '#EEF0F6';
	}
}
function showMsg() {
	var vh = document.getElementById('xspace-sitemsg').style.bottom;
	if (vh=='') {vh='-180px'}
	var vhLen = vh.length-2;
	var vhNum = parseInt(vh.substring(0,vhLen));
	
	if (vhNum<10) {
		document.getElementById('xspace-sitemsg').style.bottom = (vhNum+5)+'px';
		showvotetime = setTimeout("showMsg()",1);
	} else {
		floatMsg();
	}
}
function closeMsg() {
	document.getElementById('xspace-sitemsg').style.display = 'none';
	CreatCookie('readMsg','1');
}


/*Cookie操作*/
function CreatCookie(sName,sValue){
	var expires = function(){ //Cookie保留时间
		var mydate = new Date();
		mydate.setTime(mydate.getTime + 3*30*24*60*60*1000);
		return mydate.toGMTString();
	}
	document.cookie = sName + "=" + sValue + ";expires=" + expires;
}
function GetCookieVal(offset) {//获得Cookie解码后的值
	var endstr = document.cookie.indexOf (";", offset);
	if (endstr == -1)
	endstr = document.cookie.length;
	return unescape(document.cookie.substring(offset, endstr));
}
function GetCookie(sName) {//获得Cookie
	var arg = sName + "=";
	var alen = arg.length;
	var clen = document.cookie.length;
	var i = 0;
	while (i < clen)
	{
		var j = i + alen;
		if (document.cookie.substring(i, j) == arg)
		return GetCookieVal (j);
		i = document.cookie.indexOf(" ", i) + 1;
		if (i == 0) break;
	}
	return null;
}

function DelCookie(sName,sValue){ //删除Cookie
	document.cookie = sName + "=" + escape(sValue) + ";expires=Fri, 31 Dec 1999 23:59:59 GMT;";
}

//显示工具条
function hidetoolbar() {
	window.parent.document.getElementById("toolbarframe").style.display="none";
}
function showtoolbar() {
	document.getElementById("toolbarframe").style.display = "block";
}
function mngLink(obj) {
	var wrap = window.parent.document.getElementById('wrap');
	if(wrap == null) {
		alert('本按钮仅对拖拽模板有效！');
		return false;
	}
	if (wrap.className=='') {
		wrap.className = 'showmnglink';
		obj.innerHTML = '隐藏编辑按钮';
	} else {
		wrap.className = '';
		obj.innerHTML = '显示编辑按钮';
	}
}

//复制URL地址
function setCopy(_sTxt){
	if(navigator.userAgent.toLowerCase().indexOf('ie') > -1) {
		clipboardData.setData('Text',_sTxt);
		alert ("网址“"+_sTxt+"”\n已经复制到您的剪贴板中\n您可以使用Ctrl+V快捷键粘贴到需要的地方");
	} else {
		prompt("请复制网站地址:",_sTxt); 
	}
}

//加入收藏
function addBookmark(site, url){
	if(navigator.userAgent.toLowerCase().indexOf('ie') > -1) {
		window.external.addFavorite(url,site)
	} else if (navigator.userAgent.toLowerCase().indexOf('opera') > -1) {
		alert ("请使用Ctrl+T将本页加入收藏夹");
	} else {
		alert ("请使用Ctrl+D将本页加入收藏夹");
	}
}

function findPosX(obj)
{
	var curleft = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curleft += obj.offsetLeft
			obj = obj.offsetParent;
		}
	}
	else if (obj.x)
		curleft += obj.x;
	return curleft;
}
function findPosY(obj)
{
	var curtop = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curtop += obj.offsetTop
			obj = obj.offsetParent;
		}
	}
	else if (obj.y)
		curtop += obj.y;
	return curtop;
}

//显示个人分类
var oldCateList;
function showHideCatList(action, id, menu, left, top, width) {
	var cateList = getbyid(menu);
	var t = 0;
	if(!left) left = 0;
	if(!top) top = 30;
	if (cateList != null) {
		var menuX = findPosX(getbyid(id))+left;
		var menuY = findPosY(getbyid(id))+top;
		//alert(menuX+' / '+menuY);
		
		if (action == 'show') {
			clearTimeout(document.t);
			if (oldCateList) {
				//alert (oldCateList.id);
				oldCateList.style.display = 'none';
			}
			cateList.style.display = 'block';
			if (!width) {
				cateList.style.width = '120px';
			} else {
				cateList.style.width = width+'px';
			}
			//alert(w+'/'+cateList.style.width);
			cateList.style.left = parseInt(menuX) + 'px';
			cateList.style.top = parseInt(menuY)+ 'px';
			oldCateList = cateList;
		} else if (action == 'hide') {
			document.t = setTimeout(function(){cateList.style.display = 'none'},500);
		}
	}
}

//评分
function rateHover(value) {
	getbyid('xspace-rates-star').className = 'xspace-rates'+value;
	getbyid('xspace-rates-tip').innerHTML = value;
}
function rateOut() {
	var rateValue = getbyid('xspace-rates-value').value;
	getbyid('xspace-rates-star').className = 'xspace-rates'+rateValue;
	getbyid('xspace-rates-tip').innerHTML = rateValue;
}
function setRate(value, itemid) {
	getbyid('xspace-phpframe').src = siteUrl+'/batch.comment.php?action=rate&rates='+value+'&itemid='+itemid;
}
function setRateXML(value, itemid) {
	getbyid('xspace-rates-value').value = value;
	if(value != '0') {
		var x = new Ajax('statusid', 'XML');
		x.get(siteUrl+'/batch.comment.php?action=rate&mode=xml&rates='+value+'&itemid='+itemid, function(s){
				alert(s.lastChild.firstChild.nodeValue);
		});
	}
}

function setSiteRate(value) {
	getbyid('rate-value').value = value;
	getbyid('ratesarea').className = 'rated'+value;
	getbyid('message').focus();
}

function adclick(id) {
	var x = new Ajax('statusid', 'XML');
	x.get(siteUrl + '/batch.common.php?action=adclick&id='+id, function(s){});
}
function display(id) {
	dobj = getbyid(id);
	if(dobj.style.display == 'none' || dobj.style.display == '') {
		dobj.style.display = 'block';
	} else {
		dobj.style.display = 'none';
	}
}


//显示隐藏媒体
function addMediaAction(div) {
	var thediv = getbyid(div);
	if(thediv) {
		var medias = thediv.getElementsByTagName('kbd');
		if(medias) {
			for (i=0;i<medias.length;i++) {
				if(medias[i].className=='showvideo' || medias[i].className=='showflash'|| medias[i].className=='showreal') {
					medias[i].onclick = function() {showmedia(this,400,400)};
				}
			}
		}
	}
}
function showmedia(Obj, mWidth, mHeight) {
	var mediaStr, smFile;
	if ( Obj.tagName.toLowerCase()=='a' ) { smFile = Obj.href; } else { smFile = Obj.title; }
	var smFileType = Obj.className.toLowerCase();

	switch(smFileType){
		case "showflash":
			mediaStr="<p style='text-align: right; margin: 0.3em 0; width: 400px;'>[<a href='"+smFile+"' target='_blank'>全屏观看</a>]</p><object codeBase='http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0' classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' width='400' height='260'><param name='movie' value='"+smFile+"'><param name='quality' value='high'><param name='AllowScriptAccess' value='never'><embed src='"+smFile+"' quality='high' pluginspage='http://www.macromedia.com/go/getflashplayer' type='application/x-shockwave-flash' width='400' height='260'></embed></OBJECT>";
			break;
		case "showvideo":
			mediaStr="<object width='400' classid='CLSID:6BF52A52-394A-11d3-B153-00C04F79FAA6'><param name='url' value='"+smFile+"' /><embed width='400' type='application/x-mplayer2' src='"+smFile+"'></embed></object>";
			break;
		case "showreal":
			mediaStr="<object classid='clsid:CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA' width='400' height='400' id='RealMoviePlayer' border='0'><param name='_ExtentX' value='13229'><param name='_ExtentY' value='1058'><param name='controls' value='ImageWindow'><param name='AUTOSTART' value='1'><param name='CONSOLE' value='_master'><param name='SRC' value='"+smFile+"'></object><object classid='clsid:CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA' width='400' height='30' id='RealMoviePlayerCtrl' border='0'><param name='_ExtentX' value='13229'><param name='_ExtentY' value='1058'><param name='AUTOSTART' value='1'><param name='CONTROLS' value='controlpanel'><param name='CONSOLE' value='_master'><param name='SRC' value='"+smFile+"'></object>";
	}
	
	var mediaDiv = document.getElementById(escape(smFile.toLowerCase()));
	
	if (mediaDiv) {
		Obj.parentNode.removeChild(mediaDiv);
	} else {
		mediaDiv = document.createElement("div");
		mediaDiv.id = escape(smFile.toLowerCase());
		mediaDiv.innerHTML = mediaStr;
		Obj.parentNode.insertBefore(mediaDiv,Obj.nextSibling);
	}
	return false;
}

//改变文章字体大小
function doZoom(size) {
	getbyid('articlebody').style.fontSize = size+'px';
}
//打印
function doPrint(){
	var csslink = document.getElementsByTagName('link');
	for (i=0; i<csslink.length; i++) {
		if (csslink[i].rel=='stylesheet') {
			csslink[i].disabled=true;
		}
	}

	printCSS = document.createElement("link");
	printCSS.id = 'printcss';
	printCSS.type = 'text/css';
	printCSS.rel = 'stylesheet';
	printCSS.href = siteUrl+'/css/print.css';
	
	var docHead = document.getElementsByTagName('head')[0];
	var mainCSS = csslink[0];
	docHead.insertBefore(printCSS,mainCSS);
	
	var articleTitle = document.getElementsByTagName('h1')[0];
	var cancelPrint = document.createElement("p");
	cancelPrint.id = 'cancelPrint';
	cancelPrint.style.textAlign = 'right';
	cancelPrint.innerHTML = "<a href='javascript:cancelPrint();' target='_self'>返回</a>&nbsp;&nbsp;<a href='javascript:window.print();' target='_self>打印</a>";
	getbyid('articledetail').insertBefore(cancelPrint,articleTitle);
	
	window.print();
}
function cancelPrint() {
	if (printCSS) {
		document.getElementsByTagName('head')[0].removeChild(printCSS);
	}
	
	var csslink = document.getElementsByTagName('link');
	for (i=0; i<csslink.length; i++) {
		if (csslink[i].rel=='stylesheet') {
			csslink[i].disabled=false;
		}
	}

	if (getbyid('cancelPrint')) {
		getbyid('articledetail').removeChild(getbyid('cancelPrint'));
	} 
}

//添加文章中的图片链接
function addImgLink(divID) {
	var msgarea = getbyid(divID);
	if(msgarea) {
		var imgs = msgarea.getElementsByTagName('img');
		for (i=0; i<imgs.length; i++) {
			if (imgs[i].parentNode.tagName.toLowerCase() != 'a') {
				imgs[i].title = '点击图片可在新窗口打开';
				imgs[i].style.cursor = 'pointer';
				imgs[i].onclick = function() { window.open(this.src); }
			}
		}
	}
}

function ctlent(event,id) {
	var form = getbyid(id);
	if (event.ctrlKey && event.keyCode == 13) {
		form.submit();
	}
}

function getQuote(cid) {

	var x = new Ajax('statusid', 'XML');
	x.get(siteUrl+'/batch.common.php?action=quote&cid='+cid, function(s){
		var revalue= s.lastChild.firstChild.nodeValue;
		var aimobj = null;
		if(getbyid('xspace-commentmsg') != null) {
			aimobj = getbyid('xspace-commentmsg');
		} else if(getbyid('message') != null) {
			aimobj = getbyid('message');
		}
		aimobj.value = revalue + "\n" + aimobj.value;
		aimobj.focus();
	});
}

function insertSmilies(smilieid) {
	var src = getbyid('smilie_' + smilieid).src;
	var code = getbyid('smilie_' + smilieid).alt;
	code += ' ';
	AddText(code);
}
function AddText(txt) {
	obj = getbyid('xspace-commentform').message;
	selection = document.selection;
	if(!obj.hasfocus) {
		obj.focus();
	}	
	if(typeof(obj.selectionStart) != 'undefined') {
		var opn = obj.selectionStart + 0;
		obj.value = obj.value.substr(0, obj.selectionStart) + txt + obj.value.substr(obj.selectionEnd);
	} else if(selection && selection.createRange) {
		var sel = selection.createRange();
		sel.text = txt;
		sel.moveStart('character', -strlen(txt));
	} else {
		obj.value += txt;
	}
}
function strlen(str) {
	return (str.indexOf('\n') != -1) ? str.replace(/\r?\n/g, '_').length : str.length;
}

function joingroup(gid) {
	var x = new Ajax('statusid', 'XML');
		
	x.get(siteUrl+'/batch.common.php?action=joingroup&gid='+gid, function(s){
		alert(s.lastChild.firstChild.nodeValue);
	});
}

//显示管理菜单层
function showmanagemenu() {
	var obj = getbyid('xspace-managemenu');
	if(obj.style.display == 'none') {
		obj.style.display = '';
	} else {
		obj.style.display = 'none';
	}
	return false;
}
/**
 * 显示验证码
 */
function showcode() {
	var imgcode = getbyid('xspace-imgseccode');
	if(imgcode) {
		newseccode(imgcode);
	}
}
function newseccode(obj) {
	obj.src=siteUrl+'/batch.seccode.php?'+Math.random(1);
}
/**
 * 全选
 */
function checkall(form, prefix, checkall) {
	var checkall = checkall ? checkall : 'chkall';
	for(var i = 0; i < form.elements.length; i++) {
		var e = form.elements[i];
		if(e.name != checkall && (!prefix || (prefix && e.name.match(prefix)))) {
			e.checked = form.elements[checkall].checked;
		}
	}
}
/**
 * 检测是否装了Flash播放器
 */
function _uFlash() {
	var f="-",n=navigator;
	if (n.plugins && n.plugins.length) {
		for (var ii=0;ii<n.plugins.length;ii++) {
			if (n.plugins[ii].name.indexOf('Shockwave Flash')!=-1) {
				f=n.plugins[ii].description.split('Shockwave Flash ')[1];
				break;
			}
		}
	} else if (window.ActiveXObject) {
		for (var ii=10;ii>=2;ii--) {
			try {
				var fl=eval("new ActiveXObject('ShockwaveFlash.ShockwaveFlash."+ii+"');");
				if (fl) { f=ii + '.0'; break; }
			} catch(e) {}
		}
	}
	//return f;
	if(f.indexOf("8")!=0 && f.indexOf("9")!=0) {
		alert("您的系统未安装Flash8版本及其以上的Flash播放器无法正常查看相关内容");
	}
}

/**
 * 获取窗口的高度与宽度
 */
function getWindowSize() {
  var winWidth = 0, winHeight = 0;
  if( typeof( window.innerWidth ) == 'number' ) {
    //Non-IE
    winWidth = window.innerWidth;
    winHeight = window.innerHeight;
  } else if( document.documentElement && ( document.documentElement.clientWidth || document.documentElement.clientHeight ) ) {
    //IE 6+ in 'standards compliant mode'
    winWidth = document.documentElement.clientWidth;
    winHeight = document.documentElement.clientHeight;
  } else if( document.body && ( document.body.clientWidth || document.body.clientHeight ) ) {
    //IE 4 compatible
    winWidth = document.body.clientWidth;
    winHeight = document.body.clientHeight;
  }
  return {winWidth:winWidth,winHeight:winHeight}
}
