package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestEditAllianceBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestEditAllianceBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var info:EditAllianceReq;
		public function RequestEditAllianceBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.info = this.info.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestEditAllianceBC
		{
			aid = undefined;
			uid = undefined;
			info = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.info = new EditAllianceReq(package_root).unserialize(msgObj.info);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestEditAllianceBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}