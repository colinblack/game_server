package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRandomUserResult
	{
		public static const PROTO:String = "ProtoBattle.ProtoRandomUserResult";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function ProtoRandomUserResult(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRandomUserResult
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRandomUserResult
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}