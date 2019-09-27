package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class SendNotifyResp
	{
		public static const PROTO:String = "ProtoAlliance.SendNotifyResp";
		public var package_root:*;
		public  var message:*;
		public var notify:AllianceNotifyCPP;
		public function SendNotifyResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			notify = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.notify = this.notify.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):SendNotifyResp
		{
			notify = undefined;
			this.notify = new AllianceNotifyCPP(package_root).unserialize(msgObj.notify);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SendNotifyResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}