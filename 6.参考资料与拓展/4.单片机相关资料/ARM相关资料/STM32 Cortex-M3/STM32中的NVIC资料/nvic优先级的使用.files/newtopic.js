
function divdisplay(id,st){
	if(st==1){
	document.getElementById(id).style.display='';
	}
	if(st==2)
	document.getElementById(id).style.display="none";
}
function inputs(inputid) {
	var doc = document.all;
	inertContent("[face]"+inputid+"[/face]");
}//end function

function inertContent(val) {
	if(val==''){
		alert('没有需要添加的内容！' );
		return;
	}
	document.formreply.content.value += val;
}//end function

function quickreply(){
	
		if(document.formreply.content.value=='' || document.formreply.content.value.length < 8 ){
			alert( '内容不能小于8个字符，最大30000个字符！' );
			document.getElementById("btnImage").style.visibility ="visible";
			document.formreply.content.focus();
			return false;
		}else{
			var content = document.formreply.content.value;
			content = content.replace(/\r\n/ig,"\n");
			content = content.replace(/\n\n/ig,"\n");
			content = content.replace(/\n/ig,"<br>");
			document.formreply.content.value = content;
			return true;
		}
}

var gradeForm = null;
var gradeObj = null;
function showForm( pid,uid ){
	if( gradeForm==null )
	gradeForm = document.getElementById( 'gradeForm' );
	gradeForm.pid.value = pid;
	gradeForm.uid.value = uid;
	if( gradeObj==null )
	gradeObj = document.getElementById( 'gradeDiv' );
	var formHTML = gradeObj.innerHTML;
	show_message( '系统评分',formHTML );
}
function doGrade( obj ){
	//var gradeForm = document.getElementById( 'gradeForm' );
	var gradeForm = obj;
	var pid = gradeForm.pid.value;
	var uid = gradeForm.uid.value;
	var points = gradeForm.gradePoint.value;
	var reason = gradeForm.reason.value;

	if( pid>0 && uid >0 ){
		var param = 'pid='+pid+'&uid='+uid+'&point='+points+'&reason='+reason;
		var x = new Ajax( 'statusid', "HTML" );
		x.get( 'post.php?act=doGrade&pid='+pid+'&uid='+uid+'&point='+points+'&reason='+reason,function(s){
			alert(s);
			window.location.reload();
		});
	}else{
		alert( "请输入评分设置！" );
	}
}

function addoption(obj) {
	if (obj.value=='addoption') {
		var newOption=prompt('请输入理由，最好不要超过10个字符','');
		if (newOption!=null && newOption!='') {
			var newOptionTag=document.createElement('option');
			newOptionTag.text=newOption;
			newOptionTag.value=newOption;
			try {
				obj.add(newOptionTag, obj.options[0]); // doesn't work in IE
			}
			catch(ex) {
				obj.add(newOptionTag, obj.selecedIndex); // IE only
			}
			obj.value=newOption;
		} else {
			obj.value=obj.options[0].value;
		}
	}
}


function addoptionPoint(obj) {
	if (obj.value=='addoption') {
		var newOption=prompt('请输入分值，范围为-30至30','');
		if (newOption!=null && newOption!='' && newOption<=30 && newOption>=-30 ) {
			var newOptionTag=document.createElement('option');
			newOptionTag.text=newOption;
			newOptionTag.value=newOption;
			try {
				obj.add(newOptionTag, obj.options[0]); // doesn't work in IE
			}
			catch(ex) {
				obj.add(newOptionTag, obj.selecedIndex); // IE only
			}
			obj.value=newOption;
		} else {
			obj.value=obj.options[12].value;
		}
	}
}
function shouchang(){
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?tid='+tid+'&act=sc',function(s){
		if(s==1){
			alert("成功收藏！");
		}else if (s==2){
			alert("您已收藏该主题.请不要重复成功！");
		}else if (s==3){
			alert("请先登陆!");
		}
		else alert('操作失败！请稍后在试');
	});
}
function setTop(){
	var type;
	type = document.getElementById( "topType" ).value;
	var param = 'tid='+tid+'&acode='+type+'&act=top';
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?tid='+tid+'&acode='+type+'&act=top',function(s){
		if(s==1){
			alert("文章主题置顶设置成功！");
		}
		else alert('文章主题置顶设置失败！');
		window.location.reload();
	});
}

function cancelTop(){
	var param = 'tid='+tid+'&acode=0';
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?tid='+tid+'&acode=0&act=top',function(s){
		alert(s);
		if(s==1){
			alert("文章主题置顶设置成功！");
		}
		else alert('文章主题置顶设置失败！');
		window.location.reload();
	});
}

var acodes='';
function setImportant(acode,gao){
	if(gao==2)
	document.getElementById("biaoshi").value=2;
	else
	document.getElementById("biaoshi").value=1;
	acodes=acode;
	if(acode!=0)
	document.getElementById("jinhua").style.display='';
	else setJinhua();
	
}
function setJinhua(){
	var biao=document.getElementById("biaoshi").value;
	var act='';
	if(biao==1){
		act='important';
	}else{
		act='gaoliang';
	}
	var jitxt=document.getElementById("jitxt").value;
	var jh=document.getElementById("jh").value;
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?tid='+tid+'&acode='+acodes+'&act='+act+'&jitxt='+jitxt+'&rq='+jh,function(s){
		if(s==1){
			alert("文章主题精华设置成功！");
		}
		else alert('文章主题精华设置失败！');
		window.location.reload();
	});
}
function doDelete( pid ){
	if( confirm('您真的要删除帖子吗?') ){
		return true;
	}
	return false;
}

function pinbi(tid,acode){
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?act=pinbi&tid='+tid+'&acode='+acode,function(s){
		if(s==1){
			alert("操作成功！");
		}
		else alert('操作失败！');
		window.location.reload();
	});
}
function pinbip(tid,acode){
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?act=pinbip&tid='+tid+'&acode='+acode,function(s){
		if(s==1){
			alert("操作成功！");
		}
		else alert('操作失败！');
		window.location.reload();
	});
}
function ss(tid,acode){
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?act=sj&tid='+tid+'&acode='+acode,function(s){
		if(s==1){
			alert("操作成功！");
		}
		else alert('操作失败！');
		window.location.reload();
	});
}
function move(){
	document.getElementById("yidong").style.display='';
}
//移动
function yidong(tid,sfid){
	var x = new Ajax( 'statusid', "HTML" );
	x.get( 'post.php?act=move&tid='+tid+'&sfid='+sfid+'&fid='+document.getElementById("yfid").value,function(s){
		if(s==1){
			alert("操作成功！");
		}
		else alert('操作失败！');
		window.location.reload();
	});
}
function setanswer( pid ){
	if( confirm('您真的觉得这就是你要的最佳答案吗？') ){
		var x = new Ajax( 'statusid', "HTML" );
		x.get( "post.php?act=setAnswer&pid="+pid,function(s){
			if( s==1){
				alert( "操作成功" );
				window.location.reload();
			}else{
				alert( "操作失败" );
			}
		});
	}
}

function fCopyToClicp(id){
	var a = window.location.href;
	if(navigator.userAgent.toLowerCase().indexOf('ie') > -1) {
		window.clipboardData.setData('text',a );
		alert ("连接已经复制到您的剪贴板中\n您可以使用Ctrl+V快捷键粘贴到需要的地方");
	} else {
		prompt("请复制链接地址:",a );
	}
}

function disatt(id){
	var contentatt=document.getElementById(id+"dimg");
	var attatt=document.getElementById(id+"file");
	if(contentatt){//判断是否插入
	   attatt.style.display="none";
	}else {
	   attatt.style.display="";
	}

}