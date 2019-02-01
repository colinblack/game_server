package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDonatePowerReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoDonatePowerReq";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var otherId:int;
		public function ProtoDonatePowerReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ts = undefined;
			otherId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.otherId = this.otherId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDonatePowerReq
		{
			ts = undefined;
			otherId = undefined;
			this.ts = msgObj.ts;
			this.otherId = msgObj.otherId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDonatePowerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}