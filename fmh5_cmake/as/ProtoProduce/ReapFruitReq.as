package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ReapFruitReq
	{
		public static const PROTO:String = "ProtoProduce.ReapFruitReq";
		public var package_root:*;
		public  var message:*;
		public var treeud:int;
		public function ReapFruitReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			treeud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.treeud = this.treeud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReapFruitReq
		{
			treeud = undefined;
			this.treeud = msgObj.treeud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReapFruitReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}