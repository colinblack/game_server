package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperUpgrade
	{
		public static const PROTO:String = "ProtoKeeper.KeeperUpgrade";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function KeeperUpgrade(root:*)
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
		public function unserialize(msgObj:*):KeeperUpgrade
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperUpgrade
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}