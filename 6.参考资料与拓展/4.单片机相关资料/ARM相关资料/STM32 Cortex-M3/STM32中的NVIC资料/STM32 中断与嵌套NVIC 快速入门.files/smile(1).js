var count = 1;
var imgid;
var menushow='';
for(id in smiles[defaultsmile]){
	imgid=smiles[defaultsmile][id];
	menushow += '<img src="' + imgpath + '/smile/' + smile[imgid] + '" onclick="javascript:addsmile('+imgid+');" style="cursor:pointer;margin:3px;" />';
	count++;
	if(count>db_smileshownum)break;
}
GE('menu_show').innerHTML = menushow;

function showDefault(){
	if(!IsElement('buttons')){
		initFace();
	}
	mouseover_open2('menu_smile','td_smile','2');
	showSmile(1,defaultsmile);
}

function initFace(){
	var menu_smile = GE("menu_smile");
	menu_smile.className = 'menu';
	
	var b = document.createElement("div");
	b.id = "buttons";
	b.className    = "smile";
	b.style.width  = '300px';
	b.unselectable = "on";

	var s = document.createElement("div"); //表情层
	s.id = "showsmile";
	s.style.background = "#fff";
	s.style.overflowY = "auto";
	s.style.width  = '308px';
	s.style.height = '200px';
	s.unselectable = "on";

	var c=document.createElement("div");
	c.style.cssText="clear:both";

	menu_smile.appendChild(b);
	menu_smile.appendChild(c);
	menu_smile.appendChild(s);

	var num=1;
	var buttonMenu='<div style="float:right;margin-right:3px;width:auto;" onclick="closep();" title="close"><img src='+imgpath+'/wysiwyg/close.gif></div>';
	for(f in smiledb){
		buttonMenu += '<div style="float:left" unselectable="on" onclick="showSmile('+num+',\''+f+'\');">'+smiledb[f]+'</div>';
		num++;
	}
	b.innerHTML=buttonMenu;
}

function showSmile(id,path){
	var buttons = GE("buttons");
	buttons.onmousedown = read.move;
	var smileButton = buttons.getElementsByTagName("div");
	for(var i=1;i<smileButton.length;i++){
		if(i==id){
			smileButton[i].className = "lian";
		} else{
			smileButton[i].className = "";
		}
	}
	var showsmile = GE("showsmile");
	showsmile.innerHTML = "<div id=\"loading\" style=\"padding:20px;width:80%;text-align:center\">Loading...........</div>";
	for(i in smiles[path]){
		var sid = smiles[path][i];
		var pic = document.createElement("img");
		pic.style.margin = "3px";
		pic.style.cursor = 'pointer';
		pic.id = sid;
		pic.onclick = function(){addsmile(this.id);};
		pic.src = imgpath+'/smile/'+smile[sid];
		showsmile.appendChild(pic);
	}
	GE("loading").style.display="none";
}