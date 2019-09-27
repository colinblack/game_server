package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class GetCurMissionReq
	{
		public static const PROTO:String = "ProtoMission.GetCurMissionReq";
		public var package_root:*;
		public  var message:*;
		public function GetCurMissionReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetCurMissionReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetCurMissionReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}