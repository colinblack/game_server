package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpgradeShareRewardReq
	{
		public static const PROTO:String = "ProtoBattle.UpgradeShareRewardReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public function UpgradeShareRewardReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpgradeShareRewardReq
		{
			grade = undefined;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpgradeShareRewardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}