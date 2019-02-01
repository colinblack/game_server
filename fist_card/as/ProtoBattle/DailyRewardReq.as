package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class DailyRewardReq
	{
		public static const PROTO:String = "ProtoBattle.DailyRewardReq";
		public var package_root:*;
		public  var message:*;
		public function DailyRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):DailyRewardReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DailyRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}