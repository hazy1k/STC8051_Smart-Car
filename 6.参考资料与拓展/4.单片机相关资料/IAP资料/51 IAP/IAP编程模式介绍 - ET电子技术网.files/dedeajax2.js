<!--
//xmlhttp��xmldom����
var DedeXHTTP = null;
var DedeXDOM = null;
var DedeContainer = null;
var DedeShowError = false;
var DedeShowWait = false;
var DedeErrCon = "";
var DedeErrDisplay = "��������ʧ��";
var DedeWaitDisplay = "������������...";

//��ȡָ��ID��Ԫ��
//function $(eid){
//	return document.getElementById(eid);
//}

function $DE(id) {
	return document.getElementById(id);
}

//gcontainer �Ǳ���������ɵ����ݵ�����
//mShowError �Ƿ���ʾ������Ϣ
//DedeShowWait �Ƿ���ʾ�ȴ���Ϣ
//mErrCon ����������ʲô�ַ�����Ϊ����
//mErrDisplay ��������ʱ��ʾ����Ϣ
//mWaitDisplay �ȴ�ʱ��ʾ��Ϣ
//Ĭ�ϵ��� DedeAjax('divid',false,false,'','','')

function DedeAjax(gcontainer,mShowError,mShowWait,mErrCon,mErrDisplay,mWaitDisplay){

DedeContainer = gcontainer;
DedeShowError = mShowError;
DedeShowWait = mShowWait;
if(mErrCon!="") DedeErrCon = mErrCon;
if(mErrDisplay!="") DedeErrDisplay = mErrDisplay;
if(mErrDisplay=="x") DedeErrDisplay = "";
if(mWaitDisplay!="") DedeWaitDisplay = mWaitDisplay;


//post��get�������ݵļ�ֵ��
this.keys = Array();
this.values = Array();
this.keyCount = -1;

//http����ͷ
this.rkeys = Array();
this.rvalues = Array();
this.rkeyCount = -1;

//����ͷ����
this.rtype = 'text';

//��ʼ��xmlhttp
if(window.ActiveXObject){//IE6��IE5
   try { DedeXHTTP = new ActiveXObject("Msxml2.XMLHTTP");} catch (e) { }
   if (DedeXHTTP == null) try { DedeXHTTP = new ActiveXObject("Microsoft.XMLHTTP");} catch (e) { }
}
else{
	 DedeXHTTP = new XMLHttpRequest();
}

//����һ��POST��GET��ֵ��
this.AddKey = function(skey,svalue){
	this.keyCount++;
	this.keys[this.keyCount] = skey;
	svalue = svalue.replace(/\+/g,'$#$');
	this.values[this.keyCount] = escape(svalue);
};

//����һ��Http����ͷ��ֵ��
this.AddHead = function(skey,svalue){
	this.rkeyCount++;
	this.rkeys[this.rkeyCount] = skey;
	this.rvalues[this.rkeyCount] = svalue;
};

//�����ǰ����Ĺ�ϣ�����
this.ClearSet = function(){
	this.keyCount = -1;
	this.keys = Array();
	this.values = Array();
	this.rkeyCount = -1;
	this.rkeys = Array();
	this.rvalues = Array();
};


DedeXHTTP.onreadystatechange = function(){
	//��IE6�в�����ϻ��첽ģʽ����ִ������¼���
	if(DedeXHTTP.readyState == 4){
    if(DedeXHTTP.status == 200){
       if(DedeXHTTP.responseText!=DedeErrCon){
         DedeContainer.innerHTML = DedeXHTTP.responseText;
       }else{
       	 if(DedeShowError) DedeContainer.innerHTML = DedeErrDisplay;
       }
       DedeXHTTP = null;
    }else{ if(DedeShowError) DedeContainer.innerHTML = DedeErrDisplay; }
  }else{ if(DedeShowWait) DedeContainer.innerHTML = DedeWaitDisplay; }
};

//������ģʽ��״̬
this.BarrageStat = function(){
	if(DedeXHTTP==null) return;
	if(typeof(DedeXHTTP.status)!=undefined && DedeXHTTP.status == 200)
  {
     if(DedeXHTTP.responseText!=DedeErrCon){
         DedeContainer.innerHTML = DedeXHTTP.responseText;
     }else{
       	if(DedeShowError) DedeContainer.innerHTML = DedeErrDisplay;
     }
  }
};

//����http����ͷ
this.SendHead = function(){
	if(this.rkeyCount!=-1){ //�����û������趨������ͷ
  	for(;i<=this.rkeyCount;i++){
  		DedeXHTTP.setRequestHeader(this.rkeys[i],this.rvalues[i]); 
  	}
  }
��if(this.rtype=='binary'){
  	DedeXHTTP.setRequestHeader("Content-Type","multipart/form-data");
  }else{
  	DedeXHTTP.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  }
};

//��Post��ʽ��������
this.SendPost = function(purl){
	var pdata = "";
	var i=0;
	this.state = 0;
	DedeXHTTP.open("POST", purl, true); 
	this.SendHead();
  if(this.keyCount!=-1){ //post����
  	for(;i<=this.keyCount;i++){
  		if(pdata=="") pdata = this.keys[i]+'='+this.values[i];
  		else pdata += "&"+this.keys[i]+'='+this.values[i];
  	}
  }
  DedeXHTTP.send(pdata);
};

//��GET��ʽ��������
this.SendGet = function(purl){
	var gkey = "";
	var i=0;
	this.state = 0;
	if(this.keyCount!=-1){ //get����
  	for(;i<=this.keyCount;i++){
  		if(gkey=="") gkey = this.keys[i]+'='+this.values[i];
  		else gkey += "&"+this.keys[i]+'='+this.values[i];
  	}
  	if(purl.indexOf('?')==-1) purl = purl + '?' + gkey;
  	else  purl = purl + '&' + gkey;
  }
	DedeXHTTP.open("GET", purl, true); 
	this.SendHead();
  DedeXHTTP.send(null);
};

//��GET��ʽ�������ݣ�����ģʽ
this.SendGet2 = function(purl){
	var gkey = "";
	var i=0;
	this.state = 0;
	if(this.keyCount!=-1){ //get����
  	for(;i<=this.keyCount;i++){
  		if(gkey=="") gkey = this.keys[i]+'='+this.values[i];
  		else gkey += "&"+this.keys[i]+'='+this.values[i];
  	}
  	if(purl.indexOf('?')==-1) purl = purl + '?' + gkey;
  	else  purl = purl + '&' + gkey;
  }
	DedeXHTTP.open("GET", purl, false); 
	this.SendHead();
  DedeXHTTP.send(null);
  //firefox��ֱ�Ӽ��XHTTP״̬
  this.BarrageStat();
};

//��Post��ʽ��������
this.SendPost2 = function(purl){
	var pdata = "";
	var i=0;
	this.state = 0;
	DedeXHTTP.open("POST", purl, false); 
	this.SendHead();
  if(this.keyCount!=-1){ //post����
  	for(;i<=this.keyCount;i++){
  		if(pdata=="") pdata = this.keys[i]+'='+this.values[i];
  		else pdata += "&"+this.keys[i]+'='+this.values[i];
  	}
  }
  DedeXHTTP.send(pdata);
  //firefox��ֱ�Ӽ��XHTTP״̬
  this.BarrageStat();
};


} // End Class DedeAjax

//��ʼ��xmldom
function InitXDom(){
  if(DedeXDOM!=null) return;
  var obj = null;
  if (typeof(DOMParser) != "undefined") { // Gecko��Mozilla��Firefox
    var parser = new DOMParser();
    obj = parser.parseFromString(xmlText, "text/xml");
  } else { // IE
    try { obj = new ActiveXObject("MSXML2.DOMDocument");} catch (e) { }
    if (obj == null) try { obj = new ActiveXObject("Microsoft.XMLDOM"); } catch (e) { }
  }
  DedeXDOM = obj;
};

-->
