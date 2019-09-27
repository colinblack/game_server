package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class MissionCPP
	{
		public static const PROTO:String = "ProtoMission.MissionCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var value:int;
		public function MissionCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			value = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.value = this.value;
			return serializeObj;
		}
		public function unserialize(msgObj:*):MissionCPP
		{
			id = undefined;
			value = undefined;
			this.id = msgObj.id;
			this.value = msgObj.value;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MissionCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}