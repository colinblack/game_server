package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class SeekHelpReq
	{
		public static const PROTO:String = "ProtoProduce.SeekHelpReq";
		public var package_root:*;
		public  var message:*;
		public var treeud:int;
		public function SeekHelpReq(root:*)
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
		public function unserialize(msgObj:*):SeekHelpReq
		{
			treeud = undefined;
			this.treeud = msgObj.treeud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SeekHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}