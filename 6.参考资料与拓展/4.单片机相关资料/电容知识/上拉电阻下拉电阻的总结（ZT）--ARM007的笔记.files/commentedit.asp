
var ubbimg='/';
document.write('<script src="/editor/ubb.js"></script>');
document.write("<style type='text/css'>@import url('/editor/ubb.css');</style>");
ubbhtml="<div id=\"oblog_ubb\">";
ubbhtml+="<div class=\"oblog_ubbtoolbar\">";
ubbhtml+="	<a href=\"javascript:InsertText(objActive,ReplaceText(objActive,\'[b]\',\'[\/b]\'),true);void(0)\"><img src=\""+ubbimg+"images\/bold.gif\" alt=\"粗体\"  border=\"0\" align=\"absmiddle\"><\/a>";
ubbhtml+="	<a href=\"javascript:InsertText(objActive,ReplaceText(objActive,\'[i]\',\'[\/i]\'),true);void(0)\"><img src=\""+ubbimg+"images\/italic.gif\" alt=\"斜体\" border=\"0\" align=\"absmiddle\" ><\/a>";
ubbhtml+="	<a href=\"javascript:InsertText(objActive,ReplaceText(objActive,\'[u]\',\'[\/u]\'),true);void(0)\"><img src=\""+ubbimg+"images\/underline.gif\" alt=\"下划线\" border=\"0\" align=\"absmiddle\"><\/a>";
ubbhtml+="	<a href=\"javascript:InsertText(objActive,ReplaceText(objActive,\'[quote]\',\'[\/quote]\'),true);void(0)\"><img src=\""+ubbimg+"images\/quote.gif\" alt=\"插入引用\" border=\"0\" align=\"absmiddle\"><\/a>";
ubbhtml+="	<a href=\"javascript:UBB_smiley();void(0)\"><img src=\""+ubbimg+"images\/smiley.gif\" alt=\"插入表情\" border=\"0\" align=\"absmiddle\" id=\"A_smiley\"><\/a>";
ubbhtml+="	<\/div>";
ubbhtml+="	<div id=\"oblog_ubbemot\">";
ubbhtml+="	<\/div>";
ubbhtml+="	  <textarea name=\"oblog_edittext\" cols=\"92\" rows=\"10\" id=\"oblog_edittext\" class=\"oblog_ubbtext\" onfocus=\"addcode();\" ><\/textarea>";
ubbhtml+="<\/div>";
ubbhtml+="	<div id=\"oblog_vcode\">";
ubbhtml+="	<\/div>";
if (chkdiv('oblog_edit')) {
document.getElementById('oblog_edit').innerHTML=ubbhtml;
}

if (chkdiv('UserName')) {
document.getElementById('UserName').value='访客t85Bs2';
}
if (chkdiv('Password')) {
document.getElementById('Password').value='';
}
if (chkdiv('homepage')) {
document.getElementById('homepage').value='http://';
}

function reply_quote(id)
{
	var etype='3';
	if (etype=='1'){
		oblog_editors['oblog_edittext'].setHTML("<div class='quote'><strong>以下引用"+document.all["n_"+id].innerHTML+"在"+document.all["t_"+id].innerHTML+"发表的评论:</strong><br /><br />"+document.all["c_"+id].innerHTML+"</div><br />\n");
		//oblog_editors['oblog_edittext']._iframe.contentWindow.focus();
	}else{
		var ttext=document.all["c_"+id].innerHTML
		var simg;
		var simgs="";
		var simg1;
		ttext=ttext.replace(/<BR>/g,"[br]")
		ttext=ttext.replace(/(<STRONG>)(.[^\[]*)(<\/STRONG>)/,"[b]$2[/b]");
		ttext=ttext.replace(/(<U>)(.[^\[]*)(<\/U>)/,"[u]$2[/u]");
		ttext=ttext.replace(/(<EM>)(.[^\[]*)(<\/EM>)/,"[i]$2[/i]");
		ttext=ttext.replace(/<DIV class=quote>/g,"[quote]");
		ttext=ttext.replace(/<\/DIV>/g,"[/quote]");
		ttext=ttext.replace(/\.gif">/g,".gif\">##");
		simg=ttext.split("##");
		for(var i=0;i<simg.length;i++){
			simg1=simg[i].replace(/<IMG.[^\[]*face([^\.]*)\.gif">/,"[EMOT]$1[/EMOT]");
			simgs=simgs + simg1;
			}
		ttext=simgs;
		ttext=ttext.replace(/<IMG.[^\[]*face([^\.]*)\.gif">/,"[EMOT]$1[/EMOT]");
		document.getElementById('oblog_edittext').value+="[quote][b]以下引用"+document.all["n_"+id].innerHTML+"在"+document.all["t_"+id].innerHTML+"发表的评论:[/b]\n"+ttext+"[\/quote]\n";
		document.getElementById('oblog_edittext').focus();
	}
}

function Verifycomment()
{
	var oblog_edittext = document.getElementById("oblog_edittext");
	var commenttopic = document.getElementById("commenttopic");
	if(commenttopic.value==''){
		alert("请输入标题!");
		commenttopic.focus();
		return false;
	}
	if(oblog_edittext.value==''){
		alert("请输入评论内容!");
		oblog_edittext.focus();
		return false;
	}
	
	if(document.all("CodeStr").value==''){
		alert("请输入验证码");
		document.all("CodeStr").focus();
		return false;
	}
	
}
