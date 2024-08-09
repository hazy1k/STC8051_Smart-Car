function EditorSaving(editname)
{
    var maxwidth = 400;
    var editor = document.getElementById(editname).contentWindow;
    for(var i=0;i<editor.document.images.length;i++)
    {
        var img = editor.document.images[i];
        if(img.width> maxwidth)
        {
            img.width = maxwidth;
            var a = editor.document.createElement("a");
            a.href = img.src;
            a.target = "_blank";
            
            var image = editor.document.createElement("img");
            image.src = img.src;
            image.width = maxwidth;
            image.height = img.height;
            image.alt = "点击看大图";
            a.appendChild(image);
            
            var parentNode = img.parentNode;
            parentNode.replaceChild(a,img);
        }
    }
}
function searchblog(e)
{
    var q = document.getElementById(e).value;

    if (q.length > 0) {
        url = "http://so.ednchina.com/SearchList/blog/?q=" + encodeURIComponent(q);
    	//url = "http://www.google.cn/custom?q=" + encodeURIComponent(q) + "&domains=blog.ednchina.com&sitesearch=blog.ednchina.com&forid=1&ie=utf-8&oe=utf-8&safe=active&cof=GALT%3A%23008000%3BGL%3A1%3BDIV%3A%23336699%3BVLC%3A663399%3BAH%3Acenter%3BBGC%3AFFFFFF%3BLBGC%3A336699%3BALC%3A0000FF%3BLC%3A0000FF%3BT%3A000000%3BGFNT%3A0000FF%3BGIMP%3A0000FF%3BLH%3A50%3BLW%3A88%3BL%3Ahttp%3A%2F%2Fwww.ednchina.com%2Fimages%2Fsearch_logotiny2.jpg%3BS%3Ahttp%3A%2F%2Fwww.ednchina.com%3BFORID%3A1&hl=zh-CN&sa=Google+%E6%90%9C%E7%B4%A2";
    	window.open(url);
    }
    else
    {
        alert("必须输入查询条件!");
    }
}

function resizeImages() {
    var broswer = navigator.appName;
    var b_version = navigator.appVersion
    var version = b_version.split(";");
    var trim_Version = version[1].replace(/[ ]/g, "");
    var maxwidth = 520;
    if (broswer == "Microsoft Internet Explorer" && trim_Version == "MSIE6.0") {
        var container = document.getElementById("Container");
        var conarray = container.getElementsByTagName("img");
        //alert(conarray.length);
        for (var i = 0; i < conarray.length; i++) {
            var img = conarray[i];
            if (img.width > maxwidth) {
                var editor = img.parentNode;
                img.width = maxwidth;
                var a = editor.document.createElement("a");
                a.href = img.src;
                a.style = "cursor:hand;";
                a.target = "_blank";

                var image = editor.document.createElement("img");
                image.src = img.src;
                image.width = maxwidth;
                image.height = img.height;
                image.alt = "点击看大图";
                a.appendChild(image);

                var parentNode = img.parentNode;
                parentNode.replaceChild(a, img);
            }
        }
    }
}