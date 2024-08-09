document.domain="baidu.com";
document.write('<style>#shadowDiv{display:none;width:100%;height:100%;position:absolute;top:0px:left:0px;background-color:#FFF;filter: alpha(opacity=70);opacity:0.7;z-index:65534}#popDiv{border:1px solid #78b664;display:none;position:absolute;width:450px;height:300px;z-index:65535;background-color:#fff;}a.tLink{color:#000;text-decoration: none;}</style>');
function G(id){	if(typeof(id)=="string"){return document.getElementById(id);}return id;}
String.prototype.trim=function(){
	return this.replace(/(^[\s\t\xa0\u3000]+)|([\u3000\xa0\s\t]+$)/g, "");
};

String.prototype.byteLength=function(){
	return this.replace(/[^\u0000-\u007f]/g,"\u0061\u0061").length;	
}
String.prototype.format=function(){
  if(arguments.length==0) return this;
  for(var s=this, i=0; i<arguments.length; i++)
    s=s.replace(new RegExp("\\$"+i+"\\$","g"), arguments[i]);
  return s;
};
function addEvent(ele,event,fun){
	if(typeof(window.attachEvent)!="undefined"){
		ele.attachEvent("on"+event,fun);
	}else{
		if(window.addEventListener){
			ele.addEventListener(event,fun,true);
		}
	}
}
if (![].push) Array.prototype.push = function() {
    for (var i = 0; i < arguments.length; i++) {
      this[this.length] = arguments[i];
    }
    return this.length;
  };
if (![].pop) Array.prototype.pop = function(){
    var _item = this[this.length - 1];
    this.length--;
    return _item;
  };
function proxy(){
	var __a=[];
	for(var i=0,l=arguments.length;i<l;i++){
		__a[i]=arguments[i];
	}
	var __func=__a[0];
	__a.shift();
	 return function(){__func.apply(null,__a)};
}
function changeClassName(id,className,act)
{
	var ele=G(id);
	var reg=new RegExp("\\b"+className+"\\b","g");
	var cn=ele.className.replace(className,"");
	ele.className=(act?cn+" "+className:cn);
	return true;
}
function addClassName(ele,className){
	changeClassName(ele,className,true);
}
function removeClassName(ele,className){
	changeClassName(ele,className,false);
}
function userLogin(onSucc,onFail,p){
    if(onSucc){
        onLoginSuccess=onSucc;
    }else{
        onLoginSuccess=defalutLoginSuccess;
    }
    if(onFail){
        onLoginFailed=onFail;
    }else{
        onLoginFailed=defaultLoginFail;
    }
    p = p ? "?"+p : "";
	Pop.show("登录",{url:"/userlogin.html"+p,width:400,height:300});
}
var defalutLoginSuccess=function(){window.location.reload();}
var onLoginSuccess=defalutLoginSuccess;
var loginSuccess=function(){
	Pop.hide();
	onLoginSuccess();
}
var defaultLoginFail=function(){
    window.location="http://passport.baidu.com/?login&tpl=ik&u="+escape("http://zhidao.baidu.com/");
}
var onLoginFailed=defaultLoginFail;
var loginFailed=function(){
        Pop.hide();
        onLoginFailed();
    }
FactoryXMLHttpRequest=function(){
	if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP");}
	else if(window.XMLHttpRequest){
		return new XMLHttpRequest();
	}else{return null;}
}
function request(url,onOk,onErr)
{
	var req=FactoryXMLHttpRequest();
	req.open("GET",url,true);
	req.onreadystatechange=proxy(
	function(obj,ok,err){
		if(obj.readyState==4){
			if(obj.status==200){
				ok(obj);
			}else{
				err(obj);
			}
		}
	},req,onOk,onErr);
	req.send(null);
}
function checkLogin(hasLogin,notLogin,p){
	function onOk(req,hasLogin,notLogin){
		if(!!eval("("+req.responseText+")")){
			hasLogin();
		    return true;
        }
	    userLogin(hasLogin,notLogin,p);
        return false;
	}
	request("/q?ct=28&lm=1"+ '&s=' + (new Date()).getTime(),function(req){onOk(req,hasLogin,notLogin);},hasLogin);
}
function checkLoginF(action,p){
    checkLogin(action,action,p);
}

var Pop={
	onOk:function(){},
	onclosed:function(){},
	create:function ()
	{
		if(!G("popDiv")){
			var sha=document.createElement("div");
			sha.id="shadowDiv";
			var p=document.createElement("div");
			p.id="popDiv";
            var fr=document.createElement("iframe");
            fr.id="shadowIframe";
            fr.style.filter="alpha(opacity=0)";
            fr.style.opacity="0";
            fr.style.position="absolute";
            
			p.innerHTML="<div id=\"popTitle\">"+
					"<table width=\"100%\" cellspacing=\"0\" bgcolor=\"#78b664\" cellpadding=\"0\" border=\"0\" style=\"-moz-user-select: none; height: 24px;\">"+
					"<tr><td width=\"6\" height=\"24\"\/>"+
					"<td id=\"dialogBoxTitle\" style=\"color:#fff; font-size: 14px; font-weight: bold;\"></td>"+
					"<td id=\"dialogClose\" width=\"20\" valign=\"middle\" align=\"right\">"+
						"<input id=\"dialogBoxClose\" onclick=\"Pop.hide()\" width=\"16\" type=\"image\" height=\"16\" border=\"0\" align=\"absmiddle\" title=\"关闭\" src=\"http://img.baidu.com/img/iknow/dialogclose.gif\"\/>"+
					"</td><td width=\"6\"\/>"+
					"</tr></table>"+
				"</div>"+
				"<div id=\"popBody\" style=\"display:none;text-align:center;padding:20px;font-size:14px;\"></div>"+
				"<div id=\"ifrDiv\">"+
				"<iframe id=\"popIframe\" name=\"popIframe\" width=\"98%\" frameborder=\"0\" height=\"90%\" scrolling=\"no\" src=\"about:blank\"></iframe>"+
				"</div>";
			document.body.insertBefore(fr,document.body.firstChild);
			document.body.insertBefore(p,document.body.firstChild);
            document.body.insertBefore(sha,document.body.firstChild);
			addEvent(window,"resize",Pop.resize);
		}
	},
	resize:function ()
	{
		Pop.create();
		var top=document.body.scrollTop;
		var w = document.body.scrollWidth;
		var h =document.body.scrollHeight;
		var shadowDiv = G("shadowDiv");
		var popDiv = G("popDiv");
        var sf=G("shadowIframe");
        var pw=parseInt(popDiv.style.width,10)||500;
        var ph=parseInt(popDiv.style.height,10)||500;
		shadowDiv.style.width=w+"px";
		shadowDiv.style.height=h+"px";
		shadowDiv.style.left=shadowDiv.style.top="0px";
		divLeft=(document.body.clientWidth-pw)/2;
		var divTop = (document.body.clientHeight-ph)/2+top;
		if(divLeft < 1) divLeft=top;
		if(divTop < 1) divTop="20";
		sf.style.left=popDiv.style.left = divLeft+"px";
		sf.style.top=popDiv.style.top = divTop+"px";
	},
	 hide:function()
	 {
		Pop.onclosed();
		try{
          G("popDiv").style.display = "none";
		  G("shadowDiv").style.display = "none";
          G("shadowIframe").style.width="0px";
         G("shadowIframe").style.height="0px"; 
          G("shadowIframe").style.display="none";
		}catch(uncreatepop){}
        
        try{G("popIframe").src="about:blank";}catch(e)
		{
			try{document.frames["popIframe"].location="about:blank";}catch(e){}
		}
	 },
	 config:function(title,conf){
		if(title){
			G("dialogBoxTitle").innerHTML=title;
		}
			Pop.onclosed=conf.onclosed||function(){};
		if(conf.url){
			if(conf.url!=true){
				try{G("popIframe").src=conf.url;}
				catch(e){
					try{document.frames["popIframe"].location=conf.url;}
					catch(e){}
				}
			}
			G("ifrDiv").style.display="block";
			G("popBody").style.display="none";
		}
		else{
			if(conf.info){
				G("ifrDiv").style.display="none";
				G("popBody").style.display="block";
				G("popBody").innerHTML=conf.info;
			}
		}
		var pw=conf.width||450;
		var ph=conf.height||400;
		var p=G("popDiv");
        var sf=G("shadowIframe");
		sf.style.width=p.style.width=pw+"px";
		sf.style.height=p.style.height=ph+"px";
	},
	show:function (title,conf)
	{
		Pop.create();
		Pop.config(title,conf);
		Pop.resize();
		G("popDiv").style.display = "block";
		G("shadowDiv").style.display = "block";
        G("shadowIframe").style.display="";
	},
    confirm:function(msg,conf)
	{
		Pop.onOk=proxy(function(func){Pop.onclosed=function(){};Pop.hide();func();},conf.ok||Pop.hide);
		var m="<span class='f14'>$2$</span><br><br><p align='center'><input type='button'value='$0$' onclick='Pop.onOk();'>&nbsp;&nbsp;&nbsp;&nbsp;<input type='button'value='$1$' onclick='Pop.hide()'></p>";
		m=m.format(conf.okInfo||"确定",conf.cancelInfo||"取消",msg);
		Pop.show(conf.title||"信息确认",{info:m,width:(conf.width||300),height:(conf.height||150),onclosed:conf.cancel});
	}	
}
function TopLoginSuccess(){window.location.reload();}
function TopLoginFail(){window.location="http://passport.baidu.com/?login&tpl=ik&u="+escape(location.href);}
function NewAskTop(){document.fask.word.value=document.ftop.word.value;document.fask.submit();}
function NewAskBottom(){document.fask.word.value=document.fbot.word.value;document.fask.submit();}
function AddScore(){document.faddscore.submit();}
function EditAnswer(){ if(checkcoAndsn(document.myform,'回答'))document.myform.submit(); }
function JudgeBestAnswer(){document.fpj.submit();}
