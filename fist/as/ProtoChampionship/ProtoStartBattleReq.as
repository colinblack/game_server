package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoStartBattleReq
	{
		public static const PROTO:String = "ProtoChampionship.ProtoStartBattleReq";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var props:Vector.<int>;
		public function ProtoStartBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			props = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			serializeObj.props = [];
			for(var i:int = 0;i < this.props.length;i++)
			{
				serializeObj.props.push(this.props[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoStartBattleReq
		{
			battleid = undefined;
			props = new Vector.<int>();
			this.battleid = msgObj.battleid;
			for(var i:int = 0;i < msgObj.props.length;i++)
			{
				this.props.push(msgObj.props[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoStartBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}