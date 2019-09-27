package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import laya.utils.Byte;
	public class PushNotifyReq
	{
		public static const PROTO:String = "ProtoNotify.PushNotifyReq";
		public var package_root:*;
		public  var message:*;
		public var notify:NotifyItemCPP;
		public function PushNotifyReq(root:*)
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
		public function unserialize(msgObj:*):PushNotifyReq
		{
			notify = undefined;
			this.notify = new NotifyItemCPP(package_root).unserialize(msgObj.notify);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushNotifyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}