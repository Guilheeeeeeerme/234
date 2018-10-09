let output = require('./output.js');

// http://jsfiddle.net/xameeramir/Lyr52v8w/

function rbTreeDraw(rbTree) {

	var t = {}

	if(rbTree != null){
		t["name"] = String(rbTree.key),
		t["color"] = rbTree.colour == 'black' ? '#000' : '#f00';
		t["children"] = [
			rbTreeDraw(rbTree.left),
			rbTreeDraw(rbTree.right),
		];

		return t;
	} else {
		return {
			name: "nil",
			color: "#000",
		}
	}

}

output = rbTreeDraw(output);

console.log('var datajson =', JSON.stringify(output), ';');
// console.log('var datajson =', JSON.stringify(output, null, "\t"), ';');