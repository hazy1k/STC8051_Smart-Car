/*
*	@copyright www.eefocus.com
*	@author kokko<kokko313@gmail.com>
*	@version 2006-08-08
*	@notice:这里除了函数，别的不要写！
*/
/**
*	字符编码
*/
function StrCode(str){
	if(encodeURIComponent) 
		return encodeURIComponent(str);
	if(escape) return escape(str);
}
/**
*	清空输入筐
*/
var clickCount = 0;
function clearCommentContent(oObject) {
	clickCount++;
	if (clickCount == 1) {
		oObject.value = "";
	}
}
/**
*	字符解码
*/
function UnStrCode(str){
	if(decodeURIComponent ) 
		return decodeURIComponent (str);
	if(unescape) return unescape(str);
}

/**
*	去除两端空格
*/
function Trim(s){
	var m = s.match(/^\s*(\S+(\s+\S+)*)\s*$/);
	return (m == null)?"":m[1];
}

function stripTags(str){
	var re = new RegExp("<\/?[^>]+>", "g");
	return str.replace(re, '');
}

/**
*	html字符转换
*/
function HtmlEncode(text){
	var re = {'<':'&lt;','>':'&gt;','&':'&amp;','"':'&quot;'};
	for (i in re) 
		text = text.replace(new RegExp(i,'g'), re[i]);
	return text;
}

/**
*	html字符转换
*/
function HtmlDecode(text){
	var re = {'&lt;':'<','&gt;':'>','&amp;':'&','&quot;':'"'};
	for (i in re) 
		text = text.replace(new RegExp(i,'g'), re[i]);
	return text;
}

/**
*	获取对象
*/
function gid(id){
	return document.getElementById ? document.getElementById(id):null;
}

/**
*	获取Tag对象
*/
function gname(name){
	return document.getElementsByTagName?
	document.getElementsByTagName(name):new Array()
}

/**
*	填充SELECT域
*	@param nodeString
*	@param array
*	@param defValue
*	@return void
*/
function fillSelect( nodeString,array,defValue ){
	var node= gid( nodeString );
	var optGroup;
	var option;
	var len=array.length;

	for(var i=0;i<len;i++){
		if( array[i][0]=='label' ){
			if(optGroup){
				node.appendChild(optGroup);
			}
			optGroup=document.createElement('optgroup');
			optGroup.label=array[i][1];
		}else{
			option=document.createElement("option");
			option.innerHTML=array[i][1];
			option.value=array[i][0];
			if( defValue!='' )	//默认选项
			{
				if( defValue == array[i][0] ){
					option.selected = true;
				}
			}
			if(optGroup){
				optGroup.appendChild(option);
			}else{
				node.appendChild(option);
			}
		}
	}//end for
	if(optGroup){
		node.appendChild(optGroup);
	}
}//end

/**
*	显示帮助信息
*	@param obj
*	@param tipMes
*	@return void
*/
function showHelpTip(obj,tipMes){
	obj= gid(obj);
	var browser = new Browser();
	var _i=document.createElement("div");
	_i.className="helpTip";
	if( !browser.isIE ){
		_i.style.marginLeft='25px';
	}
	_i.style.width='110px';
	_i.style.display='none';
	_i.style.position='absolute';
	_i.style.fontSize='12px';
	_i.innerHTML=tipMes;
	obj.appendChild(_i);
	obj.onmouseover=function(){ _i.style.display='block';};
	obj.onmouseout=function(){_i.style.display='none';};
	delete _i;
}//end

function addEvent(obj,evType,fn,useCapture ){
	if (obj.addEventListener){
		obj.addEventListener( evType, fn, useCapture );
		return true;
	}
	if (obj.attachEvent) 
		return obj.attachEvent( "on" + evType, fn );
	alert( "Unable to add event listener for " + 
		evType + " to " + obj.tagName );
}

function Browser(){
	var ua, s, i;
	this.isIE = false;
	this.isNS = false;
	this.isOP = false;
	this.isSF = false;
	ua = navigator.userAgent.toLowerCase();
	s = "opera";
	if ((i = ua.indexOf(s)) >= 0){
		this.isOP = true;
		return;
	}
	s = "msie";
	if ((i = ua.indexOf(s)) >= 0) {
		this.isIE = true;
		return;
	}
	s = "netscape6/";
	if ((i = ua.indexOf(s)) >= 0) {
		this.isNS = true;
		return;
	}
	s = "gecko";
	if ((i = ua.indexOf(s)) >= 0) {
		this.isNS = true;
		return;
	}
	s = "safari";
	if ((i = ua.indexOf(s)) >= 0) {
		this.isSF = true;
		return;
	}
}

function ClickButton(event, buttonid){
	var btnObj = gid(buttonid);
	if (btnObj){
		var e = (event||window.event);
		if (e.keyCode == 13){
			btnObj.click();
			return false;
		}
	}
	return true;
}

function WarpClass(eID,tID,fID,ev){
	var eObj = document.getElementById(eID);
	var tObj = document.getElementById(tID);
	var fObj = document.getElementById(fID);
	if (eObj && tObj){
		if ( !tObj.style.display || tObj.style.display == "block" )
		{
			tObj.style.display = "none";
			eObj.className = "Warp";
			if (fObj) 
				fObj.style.display = "none";
		}else{
			tObj.style.display = "block";
			eObj.className = "UnWarp";
			if (ev) eval(ev);
			if (fObj) fObj.style.display = "block";
		}
	}
}

function mcl(show, div, btn, over, padd){
	var objdiv = gid(div);
	var objbtn = gid(btn);
	if (objdiv && objbtn){
		var browser = new Browser();
		if (show){
			objdiv.style.display = "block";
			if (browser.isIE && over){
				var allselect = gname("select");
				for (var i=0; i<allselect.length; i++){
					allselect[i].style.visibility = "hidden";
				}
			}
			objdiv.style.top = (objbtn.offsetTop + objbtn.offsetHeight - 2) + "px";
			objdiv.style.left = (objbtn.offsetLeft - (padd?0:50)) + "px";
		}else{
			objdiv.style.display = "none";
			if (browser.isIE && over){
				var allselect = gname("select");
				for (var i=0; i<allselect.length; i++){
					allselect[i].style.visibility = "visible";
				}
			}
		}
	}
}

/**
*	复制到剪切板
*/
function CopyURL(){
	if (window.clipboardData){
		var copy = window.location.href;
		var ok = window.clipboardData.setData("Text", copy);
		if (ok){
			alert("已经把当前网址复制到剪贴板，\n\n"+
			"您可以使用(Ctrl+V或鼠标右键)粘贴功能，\n\n"+
				"发送到MSN、QQ、Blog或者论坛。\n");
		}
	}
}

function ScreenConvert(){
	var browser = new Browser();
	var objScreen = gid("ScreenOver");
	if(!objScreen) var objScreen = document.createElement("div");
	var oS = objScreen.style;
	objScreen.id = "ScreenOver";
	oS.display = "block";
	oS.top = oS.left = oS.margin = oS.padding = "0px";
	if (document.body.clientHeight)	{
		var wh = document.body.clientHeight + "px";
	}else if (window.innerHeight){
		var wh = window.innerHeight + "px";
	}else{
		var wh = "100%";
	}
	ww = screen.width-20;
	oS.width = ww+"px";
	oS.height = wh;
	oS.position = "absolute";
	oS.zIndex = "3";
	if ((!browser.isSF) && (!browser.isOP)){
		oS.background = "#ffffff";
	}else{
		oS.background = "#F0F0F0";
	}
	oS.filter = "alpha(opacity=40)";
	oS.opacity = 40/100;
	oS.MozOpacity = 40/100;
	document.body.appendChild(objScreen);
	//将所有的select元素设置为不可见，因为select元素在ie下会挡住层显示
	var allselect = gname("select");
	for (var i=0; i<allselect.length; i++) 
		allselect[i].style.visibility = "hidden";
}

function ScreenClean(){
	var objScreen = document.getElementById("ScreenOver");
	if (objScreen) 
		objScreen.style.display = "none";
	var allselect = gname("select");
	for (var i=0; i<allselect.length; i++) 
		allselect[i].style.visibility = "visible";
}

var t_DiglogX,t_DiglogY,t_DiglogW,t_DiglogH;

function DialogLoc(){
	var dde = document.documentElement;
	if (window.innerWidth){
		var ww = window.innerWidth;
		var wh = window.innerHeight;
		var bgX = window.pageXOffset;
		var bgY = window.pageYOffset;
	}else{
		var ww = dde.offsetWidth;
		var wh = dde.offsetHeight;
		var bgX = dde.scrollLeft;
		var bgY = dde.scrollTop;
	}
	t_DiglogX = (bgX + ((ww - t_DiglogW)/2));
	t_DiglogY = (bgY + ((wh - t_DiglogH)/2));
}

function DialogShow(showdata,ow,oh,w,h){
	ScreenConvert();
	var objDialog = document.getElementById("DialogMove");
	if (!objDialog) 
		objDialog = document.createElement("div");
	t_DiglogW = ow;
	t_DiglogH = oh;
	DialogLoc();
	objDialog.id = "DialogMove";
	var oS = objDialog.style;
	oS.display = "block";
	oS.top = t_DiglogY + "px";
	oS.left = t_DiglogX + "px";
	oS.margin = "0px";
	oS.padding = "0px";
	oS.width = w + "px";
	oS.height = h + "px";
	oS.position = "absolute";
	oS.zIndex = "5";
	oS.background = "#FFF";
	oS.border = "solid #820 1px";
	objDialog.innerHTML = showdata;
	document.body.appendChild(objDialog);
}

function DialogHide(){
	ScreenClean();
	var objDialog = document.getElementById("DialogMove");
	if (objDialog) 
	objDialog.style.display = "none";
}

var h1,w1,h2,w2;
w1 = 150;
h1 = 180;
w2 = 300;
h2 = 100;

//系统提示消息
function show_message( name,str ){
	if( name==''||name==null ) name = "系统提示信息:";
	var showbody = ""+
		'<table width="100%" border="0" cellspacing="0" cellpadding="0">'+
		'<tr >'+
		'<td bgcolor="#990000" style="font-size:12px;font-weight:bold;color:#fff;line-height:20px;padding-left: 5px;">'+name+'</td>'+
		'<td bgcolor="#990000"><div align="right" style="padding-right:5px;cursor: hand"><a onclick="return DialogHide();"> <img src="/images/icon_close.gif" width="8" height="8" border="0" /> </a></div></td>'+
		'</tr>'+
		'<tr>'+
		'<td colspan="2" style="font-size:12px;color:#333; padding:5px" align="center">'+str+'</td>'+
		'</tr>'+
		'</table>';
	DialogShow(showbody,w1,h1,w2,h2);	
}


//显示状态
function show_state( state ){
	var showbody = 
		"<div id=\"DialogTitleText\" style=\"font-size:12px;font-weight:bold;color:#333;\" align=\"center\"><table height="+h2+"><tr><td valign=\"middle\">"+state+"</td></tr></table></div>";
	DialogShow(showbody,w1,h1,w2,h2);
}

//设置函数
function SetCookie (name, value)
{
  var argv = SetCookie.arguments;
  var argc = SetCookie.arguments.length;
  var expires = (argc > 2) ? argv[2] : null;
  var path = (argc > 3) ? argv[3] : null;
  var domain = (argc > 4) ? argv[4] : null;
  var secure = (argc > 5) ? argv[5] : false;
  document.cookie = name + "=" + escape (value) +
    ((expires == null) ? "" : ("; expires=" + expires.toGMTString())) +
    ((path == null) ? "" : ("; path=" + path)) +
    ((domain == null) ? "" : ("; domain=" + domain)) +
    ((secure == true) ? "; secure" : "");
}

/**
 * 搜索高亮显示代码
 * @author kokko kokko313@gmail.com
 * @version 1.0 2007-10-31
 */
function SearchHighlight(mytag) {
    if (!document.createElement)
    {
        return;
    }
    var l = document.getElementsByTagName(mytag);
    if("" == q) return;
    words = unescape(q.replace(/\+/g,' ')).split(/\s+/);
	var pa = null;
	var cont;
    for (w=0;w<words.length;w++) {
        for(i=0;i<l.length;i++)
        {
			//if( words[w].length<2 || typeof words[w] == "number" )
				//continue;
			pa = new RegExp("("+words[w]+")","ig");
			cont = l[i].innerHTML;
			pa.exec(cont);
			l[i].innerHTML = cont.replace( pa,'<span class="red13">'+RegExp.$1+'</span>' );
        }
    }
}

/*************************old,stop used*********************/
//取得对象
function oo(obj)
{
	return document.getElementById(obj);
}

//显示错误信息
function show_error(obj,str ){
	if( str!=1 && str!='' ){
		obj.innerHTML = str;
		obj.className="error";
	}else{
		obj.className="";
		obj.innerHTML="<img src='/images/root/zc_ok.gif'>";
	}
}


/* 验证电子邮件 */
function validateEmail(s)
{
	if (s.length > 100)
	{
			return false;
	}
	 var regu = "^(([0-9a-zA-Z]+)|([0-9a-zA-Z]+[_.0-9a-zA-Z-]*[0-9a-zA-Z]+))@([a-zA-Z0-9-]+[.])+([a-zA-Z]{2}|net|NET|com|COM|gov|GOV|mil|MIL|org|ORG|edu|EDU|int|INT)$"
	 var re = new RegExp(regu);
	 if (s.search(re) != -1) {
		   return true;
	 } else {
		   return false;
	 }
}

//判断是否是禁止词汇
function isDenyword( w,dw )
{
	var isdw = false ;
	for (i=0; i<dw.length;i++)
	{
		if (w.indexOf(dw[i])!=-1)
		{
			isdw = true ;
			break ;
		}
	}
	return isdw ;
}



//判断浏览器
var ie = (navigator.appVersion.indexOf("MSIE")!=-1);//IE
var ff = (navigator.userAgent.indexOf("Firefox")!=-1);//Firefox
var faUrl = "http://www.eefocus.com";
var faTitle = '『与非网——电子专才的职业加油站（提供产业信息，技术资料，方案测评和在线教学）』';
//兼容的加入收藏函数
function addFavorite()
{
if(ie){window.external.AddFavorite(faUrl, faTitle);}
if(ff){window.sidebar.addPanel( faTitle, faUrl, 'Eefocus');}
}
//浏览器容错设置
function clearErrors() {
return true;
}
window.onerror = clearErrors;

//取得Cookie值
function GetCookie(name) {
	var cookie_start = document.cookie.indexOf(name);
	var cookie_end = document.cookie.indexOf(";", cookie_start);
	return cookie_start == -1 ? '' : unescape(document.cookie.substring(cookie_start + name.length + 1, (cookie_end > cookie_start ? cookie_end : document.cookie.length)));
}

//去除两边空格
function trim(input_blank){
    return input_blank.replace( /(^\s*)|(\s*$)/g, "" );
}