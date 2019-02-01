package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGradeBattleReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoGradeBattleReq";
		public var package_root:*;
		public  var message:*;
		public var common:BattleCommon;
		public function ProtoGradeBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGradeBattleReq
		{
			common = undefined;
			this.common = new BattleCommon(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGradeBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}