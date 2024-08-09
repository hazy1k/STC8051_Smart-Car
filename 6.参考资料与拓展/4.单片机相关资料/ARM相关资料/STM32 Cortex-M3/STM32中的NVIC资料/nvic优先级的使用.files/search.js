//function startsearch(obj){
    //if (obj.value == "请输入关键字") {
        //obj.value = "";
    //}
//}

function doseach(){
    var keyword = document.getElementById("keyword").value;
	var type = document.getElementById("searchselect").value;
    if (document.getElementById("searchselect").value != "") {
        window.open("http://www.eefocus.com/search/?searchselect="+type+"&keyword=" + encodeURIComponent(keyword));
        return false;
    }
    return true;
}

var values = new Array();
values["dictionary"] = new Array('权威、完整的电子百科词典，阅读专业文章必查','http://www.eefocus.com/search/','_blank');
values["site"] = new Array('电子业界资讯搜索','http://www.eefocus.com/search/','_self');
values["Datasheet"] = new Array('元器件数据手册一网搜尽','http://www.eefocus.com/search/dispatcher.php','_blank');
values["BuyParts"] = new Array('元器件零购查询','http://www.eefocus.com/search/dispatcher.php','_blank');


function changform(obj){
		
    //var v = values[obj];
   
    //g("searchselect").value = v;
	g("searchform").action = values[obj][1];
	g("searchform").target = values[obj][2];
	    
    if (eiki_check()) {
        g("keyword").value = values[obj][0];
    }
}

function g(sid){
    return document.getElementById(sid);
}

function startsearch(){
    if (g('keyword').value == values[g("searchselect").value][0]) {
        g('keyword').value = '';
        g('keyword').style.color = 'black';
        return;
    }
    if (g('keyword').value == '') {
        g('keyword').value = values[g("searchselect").value][0];
        g('keyword').style.color = 'gray';
        return;
    }
}

function eiki_check(){
    if (g("keyword").value == '') {
        return true;
    }
	var s = new Array("dictionary", "site", "Datasheet", "BuyParts");
    for (i = 0; i < s.length; i++) {
        if (g("keyword").value == values[s[i]][0]) {
            return true;
        }
    }
    return false;
}
function checksearch(){
	var k=g("searchselect").value;
	if(values[k][0]==g('keyword').value||g('keyword').value==''){
		alert("请填写搜索关键字！");
		return false;
	}
	return true;
}
