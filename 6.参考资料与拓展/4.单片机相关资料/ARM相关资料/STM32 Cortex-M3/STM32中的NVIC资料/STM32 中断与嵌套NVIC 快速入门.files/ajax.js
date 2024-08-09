var http_request = null;
var s_XMLHttpNameCache = null;
function send_request(url,callback,data){
	http_request = createXMLHttp();
	if (typeof(http_request) == 'undefined') {
		window.alert("Can't creat XMLHttpRequest Object.");
		return false;
	}
	nowtime	 = new Date().getTime();
	url		+= (url.indexOf('?', 0) == -1) ? '?' : '&';
	url		+= 'nowtime=' + nowtime;
	if (typeof(data) == 'undefined') {
		http_request.open('GET',url,true);
		http_request.send(null);
	} else {
		var request = data;
		http_request.open('POST',url,true);
		http_request.setRequestHeader('Content-Length', request.length);
		http_request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
		http_request.send(request);
	}
	if (typeof(callback) == 'function') {
		http_request.onreadystatechange = function () {
			if (http_request.readyState == 4) {
				if (http_request.status == 200 || http_request.status == 304) {
					callback(http_request);
				} else {
					alert("Error loading page\n" + http_request.status + ':' + http_request.statusText);
				}
			}
		}
	}
}
function createXMLHttp() {
	if (window.XMLHttpRequest) {
		var objXMLHttp = new XMLHttpRequest();
		if (objXMLHttp.readyState == null) {
			objXMLHttp.readyState = 0;
			objXMLHttp.addEventListener(
			"load",
			function () {
				objXMLHttp.readyState = 4;
				if (typeof(objXMLHttp.onreadystatechange) == "function") {
					objXMLHttp.onreadystatechange();
				}
			},
			false
			);
		}
		return objXMLHttp;
	} else if (s_XMLHttpNameCache != null) {
		return new ActiveXObject(s_XMLHttpNameCache);
	} else {
		var MSXML = [
			'MSXML2.XMLHTTP.6.0',
			'MSXML2.XMLHTTP.5.0',
			'MSXML2.XMLHTTP.4.0',
			'MSXML2.XMLHTTP.3.0',
			'MsXML2.XMLHTTP.2.6',
			'MSXML2.XMLHTTP',
			'Microsoft.XMLHTTP.1.0',
			'Microsoft.XMLHTTP.1',
			'Microsoft.XMLHTTP'
		];
		var n = MSXML.length;
		for (var i = 0; i < n; i++) {
			try {
				objXMLHttp = new ActiveXObject(MSXML[i]);
				s_XMLHttpNameCache = MSXML[i];
				return objXMLHttp;
			}
			catch(e) {}
		}
		return null;
	}
}
function ajax_convert(str){
	f = new Array(/\r?\n/gi, /\+/gi, /\&/gi);
	r = new Array('%0A', '%2B', '%26');
	for (var i = 0; i < f.length; i++){
		str = str.replace(f[i], r[i]);
	}
	return str;
}

function PwMenu(){
	this.pid  = null;
	this.obj  = null;
	this.w	  = null;
	this.w	  = null;
}

PwMenu.prototype = {

	get : function(){
		if(http_request.responseText.indexOf('<') != -1){
			GE("showmenu").innerHTML = http_request.responseText;
			GE("showmenu").className = 'menu';
			menupz(read.obj,1);
		} else{
			read.close();
			ajax.guide();
		}
	},

	guide : function(){
		GE("showmenu").innerHTML = '<div style="padding:13px 30px"><img src="'+imgpath+'/loading.gif" align="absbottom" /> 正在加载数据...</div>';
		GE("showmenu").className = 'menu';
		menupz(read.obj,1);
	},

	close : function(){
		closep();
	},

	submit : function(obj,recall){
		if(typeof recall == 'undefined' || typeof recall != 'function'){
			recall = ajax.guide;
		}
		var d = '';
		var o = obj.elements;
		for(var i=0;i<o.length;i++){
			if(o[i].name && (o[i].type != 'radio' && o[i].type != 'checkbox' || o[i].checked === true))
				d += "&" + o[i].name + "=" + convert(o[i].value);
		}
		send_request(obj.action,recall,d);
		read.close();
	},

	move : function(e){
		if(is_ie){
			document.body.onselectstart = function(){return false;}
		}
		var e  = is_ie ? window.event : e;
		var o  = GE("showmenu");
		var x  = e.clientX;
		var y  = e.clientY;
		read.w = e.clientX - parseInt(o.offsetLeft);
		read.h = e.clientY - parseInt(o.offsetTop);
		document.onmousemove = read.moving;
		document.onmouseup   = read.moved;
	},

	moving : function(e){
		var e  = is_ie ? window.event : e;
		var x  = e.clientX;
		var y  = e.clientY;
		var o  = GE("showmenu");
		o.style.left = x - read.w + 'px';
		o.style.top  = y - read.h + 'px';
	},

	moved : function(){
		if(is_ie){
			document.body.onselectstart = function(){return true;}
		}
		document.onmousemove = '';
		document.onmouseup   = '';
	}
}

var read = new PwMenu();