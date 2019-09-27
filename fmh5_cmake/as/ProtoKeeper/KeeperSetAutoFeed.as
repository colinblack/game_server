package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperSetAutoFeed
	{
		public static const PROTO:String = "ProtoKeeper.KeeperSetAutoFeed";
		public var package_root:*;
		public  var message:*;
		public var autoFeed:int;
		public function KeeperSetAutoFeed(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			autoFeed = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.autoFeed = this.autoFeed;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperSetAutoFeed
		{
			autoFeed = undefined;
			this.autoFeed = msgObj.autoFeed;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperSetAutoFeed
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}