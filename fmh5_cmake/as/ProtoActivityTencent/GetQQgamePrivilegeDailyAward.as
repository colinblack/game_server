package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class GetQQgamePrivilegeDailyAward
	{
		public static const PROTO:String = "ProtoActivityTencent.GetQQgamePrivilegeDailyAward";
		public var package_root:*;
		public  var message:*;
		public function GetQQgamePrivilegeDailyAward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetQQgamePrivilegeDailyAward
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetQQgamePrivilegeDailyAward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}