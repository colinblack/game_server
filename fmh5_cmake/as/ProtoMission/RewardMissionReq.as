package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class RewardMissionReq
	{
		public static const PROTO:String = "ProtoMission.RewardMissionReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var type:int;
		public function RewardMissionReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardMissionReq
		{
			ud = undefined;
			type = undefined;
			this.ud = msgObj.ud;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardMissionReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}