package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperSetAutoFeedResp
	{
		public static const PROTO:String = "ProtoKeeper.KeeperSetAutoFeedResp";
		public var package_root:*;
		public  var message:*;
		public var ret:int;
		public function KeeperSetAutoFeedResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ret = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ret = this.ret;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperSetAutoFeedResp
		{
			ret = undefined;
			this.ret = msgObj.ret;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperSetAutoFeedResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}