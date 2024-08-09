var ifcheck = true;
var t = null;
function newgdcode(obj,url) {
	obj.src = url + '&nowtime=' + new Date().getTime();
}
function GE(id) {
	if (document.getElementById && document.getElementById(id)) {
		return document.getElementById(id);
    } else if (document.all && document.all[id]) {
		return document.all[id];
	} else if (document.layers && document.layers[id]) {
		return document.layers[id];
	} else {
		return null;
    }
}
function findPosX(obj){
	var curleft = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curleft += obj.offsetLeft
			obj = obj.offsetParent;
		}
	} else if (obj.x) {
		curleft += obj.x;
	}
	return curleft - ietruebody().scrollLeft;
}
function findPosY(obj){
	var curtop = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curtop += obj.offsetTop
			obj = obj.offsetParent;
		}
	} else if (obj.y) {
		curtop += obj.y;
	}
	return curtop - ietruebody().scrollTop;
}
function CheckAll(form){
	for (var i=0;i<form.elements.length-2;i++) {
		var e = form.elements[i];
		if (e.type=='checkbox') {
			e.checked = ifcheck;
		}
	}
	ifcheck = ifcheck == true ? false : true;
}
function Checkdel(form,msg){
	if (GE('delete').checked==1 || GE('delete').value==1) {
		var delcheck = 0;
		for (var i=0;i<form.elements.length-2;i++) {
			var e = form.elements[i];
			if (e.type=='checkbox' && e.checked == true) {
				delcheck = 1;
				break;
			}
		}
		if (delcheck==1 && !confirm(msg)) {
			return false;
		}
	}
	return true;
}
function Changselect(id){
	GE(id).checked = 1;
}

function IsElement(id){
	return GE(id)!=null ? true : false;
}

function mouseover_open2(idName,object,type){
	if(typeof type == "undefined"){
		type = 1;
	}
	GE("showmenu").innerHTML = GE(idName).innerHTML;
	GE("showmenu").className = GE(idName).className;
	menupz(object,type);
	if(type!=2){
		document.onmouseout = doc_mouseout;
	}
	return false;
}

function menupz(obj,type){
	var o = GE("showmenu");
	o.style.display = '';
	o.style.cssText = 'FILTER:Alpha(opacity=95);opacity:0.95;left:-500px;z-index:3000';

	if(typeof obj == 'string'){
		obj = GE(obj);
	}
	if(obj == null){
		if(type == 2){
			o.style.top  = 0 + 'px';
			o.style.left = 0 + 'px';
		}else{
			o.style.top  = (ietruebody().clientHeight - o.offsetHeight)/2 + ietruebody().scrollTop + 'px';
			o.style.left = (ietruebody().clientWidth - o.offsetWidth)/2 + 'px';
		}
	} else{
		var top  = findPosY(obj);
		var left = findPosX(obj);
		if(top < ietruebody().clientHeight/2 || type>3){
			top += ietruebody().scrollTop + obj.offsetHeight;
		} else{
			top += ietruebody().scrollTop - o.offsetHeight;
		}
		if(left > (ietruebody().clientWidth)*3/5){
			left -= o.offsetWidth - obj.offsetWidth;
		}
		o.style.top  = top  + 'px';
		o.style.left = left + 'px';
	}
}

function menupz_second(obj,type){
	var o = GE("showmenu_second");
	o.style.display = '';
	o.style.cssText = 'FILTER:Alpha(opacity=95);opacity:0.95;left:-500px;z-index:3000';

	if(typeof obj == 'string'){
		obj = GE(obj);
	}
	if(obj == null){
		if(type == 2){
			o.style.top  = 0 + 'px';
			o.style.left = 0 + 'px';
		}else{
			o.style.top  = (ietruebody().clientHeight - o.offsetHeight)/2 + ietruebody().scrollTop + 'px';
			o.style.left = (ietruebody().clientWidth - o.offsetWidth)/2 + 'px';
		}
	} else{
		var top  = findPosY(obj);
		var left = findPosX(obj);
		if(top < ietruebody().clientHeight/2 || type>3){
			top += ietruebody().scrollTop + obj.offsetHeight;
		} else{
			top += ietruebody().scrollTop - o.offsetHeight;
		}
		if(left > (ietruebody().clientWidth)*3/5){
			left -= o.offsetWidth - obj.offsetWidth;
		}
		o.style.top  = top  + 'px';
		o.style.left = left + 'px';
	}
}

function closep(type){
	if (typeof type == 'undefined') {
		type = 'down';
	}
	cookie_name = 0;
	obj = GE('showmenu');
	obj.innerHTML = '';
	obj.className = '';
	obj.style.display = 'none';
	if (type=='out') {
		removeEvent(document,'mouseout',doc_mouseout);
	} else {
		removeEvent(document,'mousedown',doc_mousedown);
	}
	return false;
}

function closep_second(type){
	if (typeof type == 'undefined') {
		type = 'down';
	}
	cookie_name = 0;
	obj = GE('showmenu_second');
	obj.innerHTML = '';
	obj.className = '';
	obj.style.display = 'none';
	if (type=='out') {
		removeEvent(document,'mouseout',doc_mouseout);
	} else {
		removeEvent(document,'mousedown',doc_mousedown);
	}
	return false;
}

function removeEvent(el,evname,func){
	if(is_ie){
		el.detachEvent("on" + evname,func);
	} else{
		el.removeEventListener(evname,func,true);
	}
}

function closem (){
	t = setTimeout("closep();",100);
}

function closem_second(){
	t = setTimeout("closep_second();",100);
}

function in_array(str,a){
	for(var i=0;i<a.length;i++){
		if(str == a[i])	return true;
	}
	return false;
}

function open_menu(idName,object,type){
	clearTimeout(t);
	o = GE('showmenu');
	if(typeof type == "undefined"){
		type = 1;
	}
	o.innerHTML = GE(idName).innerHTML;
	o.className = GE(idName).className;
	menupz(object,type);
	if(type!=2){
		GE(object).onmouseout = function(){
			closem();
			GE(object).onmouseout = '';
		}
		o.onmouseout = closem;
		o.onmouseover = function(){
			clearTimeout(t);
		}
	}
}

function open_menu_second(idName,object,type){
	clearTimeout(t);
	o = GE('showmenu_second');
	if(typeof type == "undefined"){
		type = 1;
	}
	o.innerHTML = GE(idName).innerHTML;
	o.className = GE(idName).className;
	menupz_second(object,type);
	if(type!=2){
		GE(object).onmouseout = function(){
			closem_second();
			GE(object).onmouseout = '';
		}
		o.onmouseout = closem_second;
		o.onmouseover = function(){
			clearTimeout(t);
		}
	}
}
	
function ietruebody(){
	return (document.compatMode && document.compatMode!='BackCompat') ? document.documentElement : document.body;
}

