function Digg_Mouseout(e)
{
    if(e.className != "clicked")
    {
        e.className = "unclicked";
    }
}

function Digg_Mouseover(e)
{
    if(e.className != "clicked")
    {
        e.className = "hover";
    }
}

function UpdateDisplay(objname,e)
{
   var obj = document.getElementById(objname);
   
   if(obj != null)
   {
       window.setTimeout("effect('"+objname+"',-1)",100);
       e.className= "clicked";        
   }
}

function effect(objname,setp)
{
   var obj = document.getElementById(objname);
   
   //css3
   var opacity = parseFloat(obj.style.opacity);
   if(setp == -1)
   {
       if(opacity >= 0.1)
       {
           var css3 = setp * 0.1;    
           obj.style.opacity = opacity + css3;
           var ie = opacity * 100;
           obj.style.filter = "alpha(opacity="+ie+")";
           window.setTimeout("effect('"+objname+"',-1)",100);
           return;
       }else{
           var i = parseInt(obj.innerHTML);
           i++;        
           obj.innerHTML = i;
           window.setTimeout("effect('"+objname+"',1)",100)
       }
   }
   
   if(opacity <= 1 && setp == 1)
   {
       var css3 = setp * 0.1;    
       obj.style.opacity = opacity + css3;
       var ie = opacity * 100;
       obj.style.filter = "alpha(opacity="+ie+")";
       window.setTimeout("effect('"+objname+"',1)",100)
       return;
   }
}

function DiggClientCallBack(arg, context)
{
    if(arg != null && arg != "")
    {
        if(arg == "请先登录")
        {
            if(window.confirm("您还没有登录呢，是否现在登录？"))
            {
                var location = "/member/myoffice/login.aspx?ReturnUrl="+escape(window.location);
                window.location = location;
            }
            return;
        }
        
        if(arg == "为了尽量保证博客大赛的公平性，您当天对任意一位博友的投票票数不能超过10票")
        {
            alert("为了尽量保证博客大赛的公平性，您当天对任意一位博友的投票票数不能超过10票");
            return; 
        }
        
        if(arg=="现在暂时禁止新用户投票")
        {
            alert("现在暂时禁止新用户投票");
            return;
        }
        
        eval(arg);
    }
}
