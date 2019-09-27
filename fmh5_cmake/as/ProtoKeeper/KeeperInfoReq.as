package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperInfoReq
	{
		public static const PROTO:String = "ProtoKeeper.KeeperInfoReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function KeeperInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperInfoReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}