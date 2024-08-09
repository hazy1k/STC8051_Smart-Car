function trim(psText) {
	if (psText != null)
	{
		psText = psText.replace(/^[\s]+/g,"");
		psText = psText.replace(/[\s]+$/g,"");
	}
	return psText;
}

//搜索
function qsp(r)
{
    r = trim(r);
	
	if (r.length>1)
	{
		r = window.escape(r);
		url = "?q=" + r;
		if(wwwdomain != null && wwwdomain != "")
		{
		    url += "&site="+wwwdomain
		}
		window.location = SearchUrl+url;
		
	    return true;
	}else{
	    alert("错误的输入条件");
        return false;
	}
}

function qs()
{
	var r = document.getElementById("q").value;

	qsp(r)
}

function a_qs()
{
	var r = document.getElementById("a_q").value;

	qsp(r);
}

function qs2(q,ue)
{
    var r = document.getElementById(q).value;

	r = trim(r);
	
	if (r.length>1)
	{
		r = window.escape(r);
		window.location = SearchUrl + ue+"?site="+wwwdomain+"&q=" + r
	    return true;
	}else{
	    alert("错误的输入条件");
        return false;
	}
}
//eekoo搜索
function eekoo(e)
{
	oC = e.parentNode.parentNode.childNodes;
	for ( var i = 0; i < oC.length; i ++ )
	{
		if ( oC[i].className == 'search_button_active' )
		{
		    oC[i].className = 'search_button_normal';
		}
	}
	e.parentNode.className = 'search_button_active';
	return false;
}

function eekooCheck()
{
	var r = document.getElementById("q").value;
	eekooSearch(r);
}

function eekooSimpleSearch(t)//t是点击进来的入口,在这里是image
{
    var b = true;//输入信息默认为真
    var url = '';
    
    var tp = t.parentNode;
    
    var tc = tp.childNodes;
        
    var v = '&t=1';//默认是站内搜索
     
    var tpp =tp.parentNode;
    var tcc = tpp.childNodes;
    var q ;
    for(var i = 0 ; i < tcc.length;i++)
    {
        if(tcc[i].id == 'q' )
        {
            q = tcc[i];
        }
    }
    
    var r =q.value;
         
    for(var i = 0 ; i < tc.length;i++)
    {
        if(tc[i].type == 'radio' && tc[i].checked == true)
        {
            if(tc[i].value == '') //站外搜索
            {
                v = '&t=0';
            }        
        }
    }

    if (r.length>1)
    {
        r = encodeURIComponent(r);
        url = "http://www.eekoo.com.cn/e.s?c=";
        url = url+"0";
		
        url = url + "&q=" + r;
		
        url = url + v;
		
        url = url +"&s=ednchina.com&from="+wwwdomain;
        
    }
    else
    {
        b = false;
    }
    
    if(b==true)
    {
        window.open(url);
	    return true;
	}
	else
	{
	    alert("错误的输入条件");
        return false;
	}
   
	
}

function eekooSearch(r)
{
    var r = trim(r);
	var oB = document.getElementById("search_button");
	if (r.length>1)
	{
		r = encodeURIComponent(r);
		url = "http://www.eekoo.com.cn/e.s?c=";
		
	    if(oB!=null)
	    {
	        var oC = oB.childNodes;
	        for ( var i = 0; i < oC.length; i ++ )
	        {
		        if ( oC[i].className == 'search_button_active' )
		        {
		            var sUserAgent = navigator.userAgent;
		            if ( sUserAgent.indexOf("compatible") > -1 && sUserAgent.indexOf("MSIE") > -1 )
		            {
		                if (oC[i].childNodes[0].id==11 && r.length < 3)
		                {
	                        alert("请输入多于两个字符的器件名！");
                            return false;
		                }
		                url = url+oC[i].childNodes[0].id;
		            }else{
		                if (oC[i].childNodes[1].id==11 && r.length < 3)
		                {
	                        alert("请输入多于两个字符的器件名！");
                            return false;
		                }
		                url = url+oC[i].childNodes[1].id;
		            }
		        }
	        }
	    }
	    else
	    {
            url = url+"0";
	    }
		url = url + "&q=" + r;
		var obj=document.getElementById("eekoo_right").childNodes;
		for(i=0;i<obj.length;i++){
		    if(obj[i].checked)
		    {
		        if(obj[i].value=="")
		        {
		            url = url + "&t=0";
                }
                else
                {
		            url = url + "&t=1";
                }
		    }
		}
		url = url +"&s=ednchina.com&from="+wwwdomain;
		window.open(url);
	    return true;
	}else{
	    alert("错误的输入条件");
        return false;
	}
}
function eekooSearchKeydown(e)
{
    var oEvent=window.event ? window.event:arguments[0];
    
    if(oEvent.keyCode==13)
    {
        return eekooSearch(arguments[0].value);
    }else{
        return true;
    }
} 

//submitForm
function submitForm(e,domainurl)
{
	var r = document.getElementById(e).value;
	
	r = trim(r);
	if(r=='输入您的电子邮件地址'||r=='')
	{
	    alert('输入您的电子邮件地址');	    
	    document.getElementById(e).focus();
	    document.getElementById(e).value='';
	    return;
	}
	if (r.length>0)
	{
		r = encodeURIComponent(r);
		
		var ue="http://www.ednchina.com/member/eLetter.aspx?email="+r;//跳转到EDNCHINA改版前的登记页面
		//var ue="/member/eLetter.aspx?email="+r; //原内容
		if(domainurl!=''&& domainurl!=undefined)
		{				  
		    window.location = escape(domainurl) + ue;
		    return;
		}	
		//window.location = ue;//原内容
		window.parent.location = ue;
	}
}

//Remove Unit
function RemoveUnit()
{
    var b = new BrowserInfo();
    var l = (parseInt(b.version)>=4 && b.name == "Microsoft Internet Explorer")?0:1   
    for(var i=0; i< document.getElementsByTagName("UL").length;i++)
    {
        if  (document.getElementsByTagName("UL")[i].childNodes.length== 0)
        {
            document.getElementsByTagName("UL")[i].parentNode.parentNode.style.display = "none";
        }
    }
}

/*
全局变量
*/

/* 广告统计脚本变量 */
var ad_list = "";

/* 顶部广告 */
var varTopAdvertisement = null;

/* 是否进入常规统计 */
var IsStat = true;

/* Domain */
var SearchUrl = "/Search/Default.aspx";
var wwwdomain = "";
/*
*   Goodspeed
*
*/

//用于集中浏览器信息的 JavaScript 类。
// Example:
// var b = new BrowserInfo();
// alert(b.version); 
function BrowserInfo() { 
    this.name = navigator.appName; 
    this.codename = navigator.appCodeName; 
    this.version = navigator.appVersion.substring(0,4); 
    this.platform = navigator.platform; 
    this.javaEnabled = navigator.javaEnabled(); 
    this.screenWidth = screen.width; 
    this.screenHeight = screen.height;
} 

//产生随机数
function getRandom(){return getRandomDomain(0,1000);}
function getRandomDomain(min,max){var now=new Date();var number = now.getSeconds();number=parseInt(Math.random(number)*(max-min+1))+min;return number;}


//抓取网页
function InitAjax()
{
var ajax=false; 
try { ajax = new ActiveXObject("Msxml2.XMLHTTP"); } 
catch (e) { try { ajax = new ActiveXObject("Microsoft.XMLHTTP"); } catch (E) { ajax = false; } }
if (!ajax && typeof XMLHttpRequest!='undefined') { ajax = new XMLHttpRequest(); } 
return ajax;
}

function PostData(url, post)
{
    var xmlhttp = InitAjax();
    //var xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	xmlhttp.Open("POST", url, false);
	xmlhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded")
	xmlhttp.send(post);
	return xmlhttp.responseText;
}


/* 获取绝对位置 */
function getObjTop(obj)
{
    var t = obj.offsetTop;
    while(obj=obj.offsetParent){
        t+=obj.offsetTop;
    }
    return t;
}

function getObjLeft(obj)
{
    var t = obj.offsetLeft;
    while(obj=obj.offsetParent){
        t+=obj.offsetLeft;
    }   
    return t;
}
 /* 寻找最近的控件 */
function FindClosestControl(e,tagName)
{
    while(e.tagName != tagName)
    {
        if (e.parentElement == null)
        {
            return null;
        }
        e = e.parentElement;
    }    
    return e
}

Array.prototype.remove=function(dx)
  {
    if(isNaN(dx)||dx>this.length){return false;}
    for(var i=0,n=0;i<this.length;i++)
    {
        if(this[i]!=this[dx])
        {
            this[n++]=this[i]
        }
    }
    this.length-=1;
  }
  
  //删除确认
function DelConfirm()
{
    var o = window.event.srcElement;
    if (o.innerText == "删除")
    {
        return DeleteConfirm();
    }
        
    return true;
}
    
function DeleteConfirm()
{
    return window.confirm("确认删除吗？");
}

function GetSkinName()
{
	var url = document.referrer;
	var url_array = url.split('/');
	if(url_array.length >= 4)
	{
	    if(url_array[3].toLowerCase() == '')
	    {
	        return "Article";
	    }
	    if(url_array[3].toLowerCase() != 'news' 
	    && url_array[3].toLowerCase() != 'solution'
	    && url_array[3].toLowerCase() != 'techchannel'
	    && url_array[3].toLowerCase() != 'designmanager'
	    && url_array[3].toLowerCase() != 'download'
	    && url_array[3].toLowerCase() != 'member'
	    && url_array[3].toLowerCase() != 'event'
	    && url_array[3].toLowerCase() != 'blog'
	    && url_array[3].toLowerCase() != 'techclass')
	    {
	        return "Article";
	    }
		return url_array[3];
	}

	return "Article";
}

function GetColumnName()
{
    switch(GetSkinName().toLowerCase())
    {
        case "article":
        return "首页";
        case "news":
        return "资讯";
        case "solution":
        return "方案";
        case "techchannel":
        return "技术";
        case "designmanager":
        return "设计经理人";
        case "download":
        return "下载";
        case "member":
        return "黄页";
        case "event":
        return "活动";
        case "blog":
        return "博客";
        case "techclass":
        return "技术分类";
        default:
        return "首页";
    }
}
//index.js--切换层的效果
function ChangeLayer(obj)
    {
        objTopParent=obj.parentNode.parentNode;
        objParent = obj.parentNode;
        var titleArray = new Array();
        var flag=0;
        for(var i=0;i<objParent.childNodes.length;i++)
        {
            if(objParent.childNodes[i].id != null && objParent.childNodes[i].id != "")
            {
                titleArray[flag]=objParent.childNodes[i];
                flag++;
            }
        }
        var contentArray = new Array();
        flag=0;
        for(var i=0;i<objTopParent.childNodes.length;i++)
        {
            if(objTopParent.childNodes[i].id != null && objTopParent.childNodes[i].id != "")
            {
                contentArray[flag]=objTopParent.childNodes[i];
                flag++;
            }
        }
        
        var oTitle = document.getElementById(titleArray[0].id);
        var oTitle2 = document.getElementById(titleArray[1].id);
        var oContent = document.getElementById(contentArray[0].id);
        var oContent2 = document.getElementById(contentArray[1].id);
        
        obj.childNodes[0].className = 'link_white';
        obj.className = 'right_title_content';
        
        if(titleArray[0].id == obj.id)
        {
            oContent2.style.display = "none";
            oContent.style.display = "block";
            oTitle2.className = "right_title_content2";
            oTitle2.childNodes[0].className = "";
        }
        if(titleArray[1].id == obj.id)
        {
            oContent2.style.display = "block";
            oContent.style.display = "none";
            oTitle.className = "right_title_content2";
            oTitle.childNodes[0].className = "";
        }
    }
//多层切换 - aysun
function ChangeManyLayer(obj)
{
    var objParentDiv = obj.parentNode;
    var IsDiv = false;
    if(objParentDiv.nodeName=='DIV')
    {        
        IsDiv = true;
    }
    for(var i=0;i<objParentDiv.childNodes.length;i++)
    {
       objParentDiv.childNodes[i].className=""; 
    }   
    if(IsDiv==false)
    {
        objParentDiv = objParentDiv.parentNode;
        
    }    
   
    if(objParentDiv.nodeName=='DIV')
    {        
        IsDiv = true;
    } 
    if(IsDiv==true)
    {
        //获取最大的DIV
        var rootNode = objParentDiv.parentNode;
        
        var LayerRootNode;
        for(var i=0;i<rootNode.childNodes.length;i++)
        {
            if(rootNode.childNodes[i].nodeName =='DIV')
            {
                if(rootNode.childNodes[i].id !=objParentDiv.id)
                {  
                    LayerRootNode = rootNode.childNodes[i]; 
                    
                }
                
            }
        }
        
        for(var i=0;i<LayerRootNode.childNodes.length;i++)
        {
            if(LayerRootNode.childNodes[i].nodeName=='DIV')
            {           
                if(LayerRootNode.childNodes[i].id==obj.id + 'layer')
                {
                    LayerRootNode.childNodes[i].style.display = 'block';
                }
                else
                {                    
                    LayerRootNode.childNodes[i].style.display = 'none';
                }
            } 
        } 
        
        obj.className='active';      
        
    }     
   
    
}
//index
    function FloatAd_Close(e)
    {
        var obj = e.parentElement;

        if (obj != null && obj.tagName == "DIV")
        {
            obj.style.display = "none";
        }
    }


//静态页面广告装载
function loadAdvertistment()
{
    for(var i=0;i< document.getElementsByTagName("iframe").length; i++)
    {
        var obj = document.getElementsByTagName("iframe")[i];
        if(obj.url)
        {
            var url = "/App_UserControl/AdvertisemantBar.aspx?pageid=@pageid&AdAreaID=@AdAreaID&dbid=@dbid&postback=@postback";//广告模版
            url = url.replace("@pageid",obj.url);
            url = url.replace("@AdAreaID",obj.area);
            url = url.replace("@dbid",dbid);
            url = url.replace("@postback",obj.postback);
            
            obj.src = obj.domain + url;                
        }
    }
}