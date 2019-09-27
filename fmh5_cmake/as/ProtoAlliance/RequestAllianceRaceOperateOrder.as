package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceRaceOperateOrder
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceRaceOperateOrder";
		public var package_root:*;
		public  var message:*;
		public var slot:int;
		public var operate:int;
		public var cdTs:int;
		public function RequestAllianceRaceOperateOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			slot = undefined;
			operate = undefined;
			cdTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.slot = this.slot;
			serializeObj.operate = this.operate;
			serializeObj.cdTs = this.cdTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceRaceOperateOrder
		{
			slot = undefined;
			operate = undefined;
			cdTs = undefined;
			this.slot = msgObj.slot;
			this.operate = msgObj.operate;
			this.cdTs = msgObj.cdTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceRaceOperateOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}