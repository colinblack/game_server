package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceSetFlag
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceSetFlag";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function RequestAllianceRaceSetFlag(root:*)
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
		public function unserialize(msgObj:*):RequestAllianceRaceSetFlag
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceSetFlag
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}