package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class GetNotifyResp
	{
		public static const PROTO:String = "ProtoNotify.GetNotifyResp";
		public var package_root:*;
		public  var message:*;
		public var notify:NotifyItemCPP;
		public function GetNotifyResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			notify = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.notify = this.notify.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNotifyResp
		{
			notify = undefined;
			this.notify = new NotifyItemCPP(package_root).unserialize(msgObj.notify);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNotifyResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}