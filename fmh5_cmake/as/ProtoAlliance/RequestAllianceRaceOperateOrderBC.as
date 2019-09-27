package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceOperateOrderBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceOperateOrderBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var slot:int;
		public var operate:int;
		public function RequestAllianceRaceOperateOrderBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			slot = undefined;
			operate = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.slot = this.slot;
			serializeObj.operate = this.operate;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceOperateOrderBC
		{
			aid = undefined;
			uid = undefined;
			slot = undefined;
			operate = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.slot = msgObj.slot;
			this.operate = msgObj.operate;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceOperateOrderBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}