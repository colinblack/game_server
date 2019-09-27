package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceRacePersonOrderLogItem
	{
		public static const PROTO:String = "ProtoAlliance.AllianceRacePersonOrderLogItem";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var status:int;
		public function AllianceRacePersonOrderLogItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.status = this.status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRacePersonOrderLogItem
		{
			id = undefined;
			status = undefined;
			this.id = msgObj.id;
			this.status = msgObj.status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRacePersonOrderLogItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}