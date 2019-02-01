package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoUpdateLevelReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoUpdateLevelReq";
		public var package_root:*;
		public  var message:*;
		public var martialGrade:int;
		public function ProtoUpdateLevelReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			martialGrade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.martialGrade = this.martialGrade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoUpdateLevelReq
		{
			martialGrade = undefined;
			this.martialGrade = msgObj.martialGrade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoUpdateLevelReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}