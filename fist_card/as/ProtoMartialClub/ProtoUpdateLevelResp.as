package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoUpdateLevelResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoUpdateLevelResp";
		public var package_root:*;
		public  var message:*;
		public var nextTs:int;
		public function ProtoUpdateLevelResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			nextTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextTs = this.nextTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoUpdateLevelResp
		{
			nextTs = undefined;
			this.nextTs = msgObj.nextTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoUpdateLevelResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}