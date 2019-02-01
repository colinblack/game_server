package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSDonatePowerReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoCSDonatePowerReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function ProtoCSDonatePowerReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSDonatePowerReq
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSDonatePowerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}