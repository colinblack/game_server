package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoMatchResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoMatchResp";
		public var package_root:*;
		public  var message:*;
		public var fig:String;
		public var name:String;
		public var grade:int;
		public var heroid:Vector.<int>;
		public function ProtoMatchResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			fig = undefined;
			name = undefined;
			grade = undefined;
			heroid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig;
			}
			serializeObj.name = this.name;
			serializeObj.grade = this.grade;
			serializeObj.heroid = [];
			for(var i:int = 0;i < this.heroid.length;i++)
			{
				serializeObj.heroid.push(this.heroid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoMatchResp
		{
			fig = undefined;
			name = undefined;
			grade = undefined;
			heroid = new Vector.<int>();
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = msgObj.fig;
			}
			this.name = msgObj.name;
			this.grade = msgObj.grade;
			for(var i:int = 0;i < msgObj.heroid.length;i++)
			{
				this.heroid.push(msgObj.heroid[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoMatchResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}