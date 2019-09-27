package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class OfferHelpReq
	{
		public static const PROTO:String = "ProtoProduce.OfferHelpReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var treeud:int;
		public function OfferHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			treeud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.treeud = this.treeud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferHelpReq
		{
			othuid = undefined;
			treeud = undefined;
			this.othuid = msgObj.othuid;
			this.treeud = msgObj.treeud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}