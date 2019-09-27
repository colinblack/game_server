package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ConfirmHelpReq
	{
		public static const PROTO:String = "ProtoProduce.ConfirmHelpReq";
		public var package_root:*;
		public  var message:*;
		public var treeud:int;
		public function ConfirmHelpReq(root:*)
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
		public function unserialize(msgObj:*):ConfirmHelpReq
		{
			treeud = undefined;
			this.treeud = msgObj.treeud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ConfirmHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}