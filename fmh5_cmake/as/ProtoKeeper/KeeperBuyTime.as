package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperBuyTime
	{
		public static const PROTO:String = "ProtoKeeper.KeeperBuyTime";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function KeeperBuyTime(root:*)
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
		public function unserialize(msgObj:*):KeeperBuyTime
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperBuyTime
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}